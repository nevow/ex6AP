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
    choice = new int();
    connections = new std::list<Connection *>();
    // creates a socket for connection with the clients
    sock = new Tcp(1, port);
    std::list<Point *> points;
    Map *map;
    int obstacleNum = 0;

    do {
        int flag = 0;
        // create map from user input
        map = parser.createMap();
        // if NULL then wrong input, print -1, repeat the loop
        if (map == NULL) {
            cout << "-1" << endl;
            continue;
        }
        obstacleNum = parser.getPositiveNumberFromUser();
        // if -1 then wrong input, print -1, delete the map, repeat the loop
        if (obstacleNum == -1) {
            cout << "-1" << endl;
            delete map;
            continue;
        }
        Point *obs;
        for (; obstacleNum > 0; obstacleNum--) {
            // create obstacle point
            obs = parser.createPoint();
            // if NULL then wrong input, flag is 1, break from inner loop
            if (obs == NULL) {
                flag = 1;
                break;
            }
            // push the point to the points list
            points.push_back(obs);
        }
        // if flag is 1 then wrong input in obstacles, delete the map and points, repeat the loop
        if (flag == 1) {
            cout << "-1" << endl;
            while (!points.empty()) {
                delete points.front();
                points.pop_front();
            }
            continue;
        }
        // no errors detected, break from loop
        break;
    } while (true);

    conMap = new std::map<int, Connection *>();
    // create the system operation
    so = new SystemOperations(map, conMap);
    // make the obstacles List from the input
    while (!points.empty()) {
        // make the points into obstacles
        Point *p = points.front();
        points.pop_front();
        so->addObstacle(*p);
        delete p;
    }
    pthread_mutex_init(&global_validator_locker, 0);               // lock
}

/**
 * get inputs from user and follow the commands.
 */
void MainFlow::input() {
    int id, drivers_num;
    // connectionData is used to transfer data to the connection thread
    connectionData cd;
    cd.sock = sock;
    cd.connections = connections;

    // repeat until input is 7
    do {
        // get the input from user to choose the action
        *choice = parser.getPositiveNumberFromUser();
        switch (*choice) {
            // create drivers, gets from the client
            case 1: {
                drivers_num = parser.getPositiveNumberFromUser();      // amount of drivers
                // if the input was not a valid number, print -1 and get new input
                if (drivers_num == -1) {
                    cout << "-1" << endl;
                    break;
                }
                sock->initialize(drivers_num);
                // create thread that handle with client acceptnes
                int status = pthread_create(&connection_thread, NULL, acceptClients, &cd);
                if (status) {
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
                // if trip info return NULL, then input was not good, print -1 and get new input
                if (tripInfo == NULL) {
                    cout << "-1" << endl;
                    // if the start or end points are obstacles.
                    // delete the trip info and get new input
                } else if (parser.isObstacle(tripInfo->getStart(), so->getObstacles())
                           || parser.isObstacle(tripInfo->getDestination(), so->getObstacles())
                           || (*(tripInfo->getStart()) == *(tripInfo->getDestination()))) {
                    delete tripInfo;
                } else {
                    so->addTI(tripInfo);                      // add the trip info to the system
                }
                break;
            }
                // create new Taxi
            case 3: {
                Taxi *taxi = parser.createTaxi();
                // if taxi return NULL, then input was not good, print -1 and get new input
                if (taxi == NULL) {
                    cout << -1 << endl;
                } else {
                    so->addTaxi(taxi);                        // add the taxi to the system
                }
                break;
            }
                // request for a driver location by his id
            case 4: {
                id = parser.getPositiveNumberFromUser();      // the id of the requested driver
                // not a valid input
                if (id == -1) {
                    cout << -1 << endl;
                    break;
                }
                Point *location = so->getDriverLocation(id);
                // if the id does not match any driver id, dont print any thing
                if (location) {
                    cout << *location;
                } else {
                    // the id soed not exist in the taxi center
                    cout << -1 << endl;
                }
                break;
            }
                // exit case
            case 7: {
                actionCount++;
                // wait that all clients to finish their exit
                while (validateAllReceivedInfo < connections->size()) {
                    sleep(1);
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
                // in every other case - print -1 and don't do anything.
            default: {
                cout << -1 << endl;
                continue;
            }
        }
        validateAllReceivedInfo = 0;         // initialize for the next choice
        // exit condition
    } while ((*choice) != 7);
    return;
}