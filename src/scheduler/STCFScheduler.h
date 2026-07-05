#ifndef STCF_SCHEDULER_H
#define STCF_SCHEDULER_H

#include "Scheduler.h"

class STCFScheduler : public Scheduler {
public:
    double run(std::vector<Process*>& processes, double currentTime);
};

#endif
