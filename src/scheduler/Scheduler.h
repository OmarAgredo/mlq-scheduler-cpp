#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "../model/Process.h"

class Scheduler {
public:
    virtual ~Scheduler() {}
    virtual double run(std::vector<Process*>& processes, double currentTime) = 0;
};

#endif
