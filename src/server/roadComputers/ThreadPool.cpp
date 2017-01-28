//
// ThreadPool.
//

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "ThreadPool.h"

using namespace std;

pthread_mutex_t TP_locker;

/**
 * constructor.
 * @param pool_size is who many threads to create.
 */
ThreadPool::ThreadPool(int pool_size) : poolSize(pool_size), stopCondition(0) {
    pthread_mutex_init(&TP_locker, NULL);
    // create pool pf threads
    for (int i = 0; i < poolSize; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, start_thread, (void *) this);
        if (ret != 0) {
            throw ("ThreadPool initialize was wrong");
        }
        threads.push_back(tid);
    }
}

/**
 * destructor.
 */
ThreadPool::~ThreadPool() {
    stopCondition = 1;                      // indicate the thread to finish
    // finish all the threads
    for (int i = 0; i < poolSize; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&TP_locker);

}

/**
 * execute_thread activate the task on the thread
 * @return NULL
 */
void *ThreadPool::execute_thread() {
    Task *task = NULL;
    while (true) {
        pthread_mutex_lock(&TP_locker);                      // lock
        while (tasks.empty()) {
            // if it's need to get out, finish
            if (stopCondition == 1) {
                pthread_mutex_unlock(&TP_locker);            // unlock
                return NULL;
            }
            // else - there aren't task, wait
            sleep(1);
        }
        task = tasks.front();
        tasks.pop_front();
        pthread_mutex_unlock(&TP_locker);                    // unlock
        (*task)();                                           // activate the task on the thread
    }
    return NULL;
}

/**
 * @param task to add
 */
void ThreadPool::add_task(Task *task) {
    tasks.push_back(task);
}

/**
 * static method.
 * @param arg is the thread pool to start with
 * @return NULL
 */
void *start_thread(void *arg) {
    ThreadPool *tp = (ThreadPool *) arg;
    tp->execute_thread();
    return NULL;
}