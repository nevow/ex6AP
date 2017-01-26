//
// ThreadPool.
//

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "ThreadPool.h"

using namespace std;

pthread_mutex_t TP_locker;

ThreadPool::ThreadPool(int pool_size) : poolSize(pool_size), stopCondition(0) {
    pthread_mutex_init(&TP_locker, NULL);
    for (int i = 0; i < poolSize; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, start_thread, (void *) this);
        if (ret != 0) {
            throw ("ThreadPool initialize was wrong");
        }
        threads.push_back(tid);
    }
    cout << poolSize << " threads created by the thread pool" << endl;

}

ThreadPool::~ThreadPool() {
    stopCondition = 1;
    for (int i = 0; i < poolSize; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&TP_locker);
}

void *start_thread(void *arg) {
    ThreadPool *tp = (ThreadPool *) arg;
    tp->execute_thread();
    return NULL;
}

void *ThreadPool::execute_thread() {
    Task *task = NULL;
    while (true) {
        pthread_mutex_lock(&TP_locker);              // lock
        while (tasks.empty()) {
            if (stopCondition == 1) {
                pthread_mutex_unlock(&TP_locker);           // unlock
                return NULL;
            }
            sleep(1);
        }
        cout << "ThreadPool: took task" << endl;
        task = tasks.front();
        tasks.pop_front();
        pthread_mutex_unlock(&TP_locker);           // unlock
        (*task)();
        cout << "ThreadPool: finished task" << endl;

    }
    return NULL;
}

int ThreadPool::add_task(Task *task) {
    tasks.push_back(task);
}

