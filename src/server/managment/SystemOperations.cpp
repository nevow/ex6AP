//
// SystemOperations.
//

#include <map>
#include "SystemOperations.h"
#include "../roadComputers/BFS.h"

// global map of id trips info (key) and Tasks (value)
std::map<int, Task *> computeRoadT;

/**
 * struct TArgs has Map and TripInfo
 */
struct TArgs {
    Map *grid;
    TripInfo *ti;
};

/**
 * constructor.
 * @param map1 the map to do on it the operations
 * @param conMap is a map of ints and connections.
 */
SystemOperations::SystemOperations(Map *map1, std::map<int, Connection *> *conMap) {
    map = map1;
    obstacles = new list<Node *>;
    tc = new TaxiCenter(conMap);
    x = map->getColumns();
    y = map->getRows();
    threadPool = new ThreadPool(5);
    pthread_mutex_init(&grid_locker, 0);
}

/**
 * destructor.
 */
SystemOperations::~SystemOperations() {
    pthread_mutex_destroy(&grid_locker);        // destroy the mutex
    delete (map);
    delete (tc);
    // delete all the obstacles list
    while (!obstacles->empty()) {
        delete (obstacles->front());
        obstacles->pop_front();
    }
    delete (obstacles);
    delete (threadPool);
    while (!computeRoadT.empty()) {
        std::map<int, Task *>::iterator it = (computeRoadT.begin());
        delete (it->second);
        computeRoadT.erase(it->first);
    }
}

/**
 * @return the obstacles list
 */
list<Node *> *SystemOperations::getObstacles() const {
    return obstacles;
}

/**
 * @return the x of the so
 */
int SystemOperations::getX() const {
    return x;
}

/**
 * @return the y of the so
 */
int SystemOperations::getY() const {
    return y;
}

/**
 * @param d is the Driver to add to the taxi center
 * @return the cab that set to the driver
 */
Taxi *SystemOperations::assignDriver(Driver *d) {
    Taxi *taxi = tc->getTaxiByID(d->getVehicle_id());
    d->setCab(taxi);
    tc->addDriver(d);
    return taxi;
}

/**
 * @param cab is the Taxi to add to the taxi center
 */
void SystemOperations::addTaxi(Taxi *cab) {
    tc->addTaxi(cab);
}

/**
 * @param obstacle to add to the obstacles List.
 */
void SystemOperations::addObstacle(Point obstacle) {
    Node *n = new Node(&obstacle);
    obstacles->push_front(n);
    map->setItem(n, -2);                    // set the match node on the grid to -2
}

/**
 * addTI add the tripInfo to the taxi center,
 * and create Tasks with the function ComputeRoad and the args
 * @param tripInfo is the TripInfo to add to the taxi center
 */
void SystemOperations::addTI(TripInfo *tripInfo) {
    TArgs *tArgs = new TArgs();
    tArgs->ti = tripInfo;
    tArgs->grid = map;
    Task *task = new Task(ComputeRoad, tArgs);
    threadPool->add_task(task);
    computeRoadT[tripInfo->getRideId()] = task;    // add the thread to computeRoadT map
    tc->addTI(tripInfo);                           // add the tripInfo to the taxi center
}

/**
 * @param id is the id of the driver
 * @return the Point of the driver from the taxiCenter
 */
Point *SystemOperations::getDriverLocation(int id) {
    return tc->getDriverLocation(id);
}

/**
 * move all the taxi by call Taxi Center's "moveAll"
 */
void SystemOperations::moveAll() {
    tc->moveAll();
}

/**
 * ComputeRoad use the BFS to calculate the road of the ride.
 * @param threadArgs is the struct with the argumrnts for the calculation
 * @return NULL
 */
void *SystemOperations::ComputeRoad(void *threadArgs) {
    TArgs *args = (TArgs *) threadArgs;
    Node *start = new Node(args->ti->getStart());          // the start of the road
    Point *end = (args->ti->getDestination());             // the end of the road
    CoordinatedItem *dest = args->grid->getCoordinatedItem(end->getX(), end->getY());
    // use BFS algorithm
    std::list<CoordinatedItem *> *road = BFS::use(args->grid, start, dest);
    delete start;
    args->ti->setRoad(road);        // set the road in the Trip Info
    delete (args);
    return NULL;
}