//
// ThreadPool.
//

#ifndef EX6AP_THREADPOOL_H
#define EX6AP_THREADPOOL_H

#include <sys/types.h>
#include <vector>
#include <deque>
#include "Task.h"

class ThreadPool {

private:

    int stopCondition;
    int poolSize;
    std::vector<pthread_t> threads;
    std::deque<Task *> tasks;

public:

    ThreadPool(int pool_size);

    ~ThreadPool();

    void *execute_thread();

    void add_task(Task *task);

};

static void *start_thread(void *arg);

#endif //EX6AP_THREADPOOL_H
