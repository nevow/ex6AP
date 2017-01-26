//
// Created by maayan on 21/01/17.
//

#ifndef EX6AP_TASK_H
#define EX6AP_TASK_H

class Task {

private:

    void *(*function)(void *);

    void *args;

    int finished;

public:

    Task(void *(fn_ptr)(void *), void *arg);

    ~Task() {};

    void operator()();

    int getFinished() const;
};


#endif //EX6AP_TASK_H
