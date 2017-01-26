//
// Created by maayan on 21/01/17.
//

#include <iostream>
#include "Task.h"

Task::Task(void *(fn_ptr)(void *), void *arg) : function(fn_ptr), args(arg), finished(0) {}

void Task::operator()() {
    (function)(args);
    std::cout << "TAask: changes finished to 1" << std::endl;
    finished = 1;
}

int Task::getFinished() const {
    return finished;
}
