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

    int obstacleNum = 0;
    connections = new std::list<Connection *>();
    // creates a socket for connection with the clients
    sock = new Tcp(1, port);
    std::list<Point *> points;
    Map *map;
    do {
        int flag = 0;
        // create map from user input
        map = parser.createMap();
        if (map == NULL) {
            cout << "-1" << endl;
            continue;
        }
        obstacleNum = parser.getPositiveNumberFromUser();
        if (obstacleNum == -1) {
            cout << "-1" << endl;
            delete map;
            continue;
        }
        Point *obs;
        for (; obstacleNum > 0; obstacleNum--) {
            obs = parser.createPoint();
            if (obs == NULL) {
                flag = 1;
                break;
            }
            points.push_back(obs);
        }
        if (flag == 1) {
            cout << "-1" << endl;
            while (!points.empty()) {
                delete points.front();
                points.pop_front();
            }
            continue;
        }
        conMap = new std::map<int, Connection *>();
        break;
    } while (true);

    // create the system operation
    so = new SystemOperations(map, conMap);
    // make the obstacles List from the input
    while (!points.empty()) {
        Point *p = points.front();
        points.pop_front();
        so->addObstacle(*p);
        delete p;
    }

}

/**
 * get inputs from user and follow the commands.
 */
void MainFlow::input() {
    choice = new int();
    int id, drivers_num;
    connectionData cd;
    cd.sock = sock;
    cd.connections = connections;

    do {
        // get the input from user to choose the action
        *choice = parser.getPositiveNumberFromUser();
        if (*choice == -1) {
            cout << "-1" << endl;
        }
        switch (*choice) {

            // create drivers, gets from the client
            case 1: {
                drivers_num = parser.getPositiveNumberFromUser();      // amount of drivers
                if (drivers_num == -1) {
                    cout << "-1" << endl;
                    break;
                }
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
                // get the input for the trip info
                TripInfo *tripInfo = parser.createTripInfo(actionCount, so->getX(), so->getY());
                if (tripInfo == NULL) {
                    cout << "-1" << endl;
                } else if (parser.isObstacle(tripInfo->getStart(), so->getObstacles())
                           || parser.isObstacle(tripInfo->getDestination(), so->getObstacles())) {
                    delete tripInfo;
                } else {
                    so->addTI(tripInfo);                        // add the trip info to the system
                }
                break;
            }
                // create new Taxi
            case 3: {
                Taxi *taxi = parser.createTaxi();
                if (taxi == NULL) {
                    cout << -1 << endl;
                } else {
                    so->addTaxi(taxi);                       // add the taxi to the system
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
                } catch (...) {
                    cout << -1 << endl;
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
                continue;
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