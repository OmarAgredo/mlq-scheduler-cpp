#ifndef MLQ_SCHEDULER_H
#define MLQ_SCHEDULER_H

#include <vector>
#include "../model/Process.h"

class MLQScheduler {
public:
    void run(std::vector<Process>& processes);
};

#endif
