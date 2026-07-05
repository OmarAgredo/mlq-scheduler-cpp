#ifndef ROUND_ROBIN_SCHEDULER_H
#define ROUND_ROBIN_SCHEDULER_H

#include "Scheduler.h"

class RoundRobinScheduler : public Scheduler {
private:
    double quantum;

public:
    explicit RoundRobinScheduler(double quantum);
    double run(std::vector<Process*>& processes, double currentTime);
};

#endif
