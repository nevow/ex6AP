//
// Task.
//

#include "Task.h"

/**
 * @param fn_ptr is the function to run
 * @param arg are the arguments to ryn with the function
 */
Task::Task(void *(fn_ptr)(void *), void *arg) : function(fn_ptr), args(arg), finished(0) {}

/**
 * operator overloding to ().
 * run the function with the arguments.
 * whan the function finish to run, change the finished flag to 1
 */
void Task::operator()() {
    (function)(args);
    finished = 1;
}

/**
 * @return 1 if finish, 0 else.
 */
int Task::getFinished() const {
    return finished;
}
