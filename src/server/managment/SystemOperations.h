//
// SystemOperations.
//

#ifndef EX1_SYSTEMOPERATIONS_H
#define EX1_SYSTEMOPERATIONS_H

#include <list>
#include "../coordinates/Node.h"
#include "../tripOperations/TaxiCenter.h"
#include "../coordinates/Map.h"
#include "../listeners/EventListener.h"
#include "../roadComputers/ThreadPool.h"

extern pthread_mutex_t grid_locker;
extern std::map<int, Task *> computeRoadT;

using namespace std;

class SystemOperations {

private:
    int x;
    int y;
    list<Node *> *obstacles;
    TaxiCenter *tc;
    Map *map;
    ThreadPool *threadPool;

public:

    SystemOperations(Map *map, std::map<int, Connection *> *cm);

    ~SystemOperations() {
        pthread_mutex_destroy(&grid_locker);        // destroy the mutex
        delete (map);
        delete (tc);
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

    int getX() const;

    int getY() const;

    Taxi *assignDriver(Driver *d);

    void addTaxi(Taxi *cab);

    void addObstacle(Point obstacle);

    void addTI(TripInfo *tripInfo);

    Point *getDriverLocation(int id);

    void moveAll();

    static void *ComputeRoad(void *tripInfo);

    list<Node *> *getObstacles() const;
};


#endif //EX1_SYSTEMOPERATIONS_H
