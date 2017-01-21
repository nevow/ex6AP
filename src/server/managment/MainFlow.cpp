//
// MainFlow.
//

#include "MainFlow.h"

using namespace std;

int validateAllReceivedInfo = 0;
int actionCount = 0;

/**
 * constructor.
 * initialize the environment, get map, obstacles and create a SystemOperations.
 */
MainFlow::MainFlow(int port) {

    int rows, columns, obstacleNum;
    connections = new std::list<Connection *>();
    // creates a socket for connection with the clients
    sock = new Tcp(1, port);

    // cerate map from user input
    Map *map = parser.createMap();

    // get the obstacle amount
    obstacleNum = ProperInput::validInt();
    cin.ignore();
    conMap = new std::map<int, Connection *>();
    // create the system operation
    so = new SystemOperations(map, conMap);
    Point *obs;
    // make the obstacles List from the input
    for (; obstacleNum > 0; obstacleNum--) {
        obs = parser.createPoint();
        so->addObstacle(*obs);
        delete (obs);
    }
}

/**
 * get inputs from user and follow the commands.
 */
void MainFlow::input() {
    char input;
    choice = new int();
    int id, drivers_num, taxi_type, num_passengers, trip_time;
    double tariff;
    char trash, manufacturer, color;
    connectionData cd;
    cd.sock = sock;
    cd.connections = connections;

    do {
        cin >> input;
        cin.ignore();
        // get the input from user to choose the action
        *choice = ProperInput::validInt();
        cin.ignore();
        switch (*choice) {

            // create drivers, gets from the client
            case 1: {
                drivers_num = ProperInput::validInt();      // amount of drivers
                cin.ignore();
                sock->initialize(drivers_num);
                // create thread that handle with client acceptnes
                int status = pthread_create(&connection_thread, NULL, acceptClients, &cd);
                if (status) {
                    cout << "problem creating thread" << endl;
                    break;
                }
                pthread_join(connection_thread, NULL);      // wait until the the thread finish
                for (std::list<Connection *>::const_iterator con = connections->begin(),
                         end = connections->end(); con != end; ++con) {
                    // receive the driver from the client
                    Driver *driver = (*con)->receiveData<Driver>();
                    // update the connection-id Driver map
                    (*conMap)[driver->getId()] = (*con);
                    // assign the Driver with the taxi, serialize the taxi, send it to the client
                    Taxi *taxi = so->assignDriver(driver);
                    (*con)->sendData<Taxi>(taxi);
                    (*con)->setOption(choice);
                }
                break;
            }
                // create new TripInfo
            case 2: {
                try {
                    // get the input for the trip info
                    TripInfo *tripInfo = parser.createTripInfo(actionCount, so->getX(), so->getY());
                    so->addTI(tripInfo);                        // add the trip info to the system
                } catch (...) {
                    cout << -1 << endl;
                }
                break;

            }
                // create new Taxi
            case 3: {
                Taxi *taxi;
                try {
                    taxi = parser.createTaxi();
                    so->addTaxi(taxi);                       // add the taxi to the system
                } catch (...) {
                    cout << -1 << endl;
                }
                break;
            }
                // request for a driver location by his id
            case 4: {
                char idString[11];
                cin.getline(idString, sizeof(idString), '\n');
                try {
                    id = parser.isValidId(idString);          // the id of the requested driver
                    Point *location = so->getDriverLocation(id);
                    if (location) {
                        cout << *location;
                    }
                } catch (string s) {
                    cout << -1 << endl;
                    cout << s << endl;
                }
                break;
            }

                // clock time - move one step
            case 9: {
                actionCount++;               // global variable that tells the threads to move
                while (validateAllReceivedInfo < connections->size()) {
                    sleep(1);
                }
                so->moveAll();
                break;
            }
                // in every other case - don't do anything.
            default: {
                break;
            }
        }
        validateAllReceivedInfo = 0;         // initialize for the next choice
        // exit condition
    } while ((*choice) != 7);
    actionCount++;
    // wait that all the clients will finish their exit
    while (validateAllReceivedInfo < connections->size()) {
        sleep(1);
    }
}