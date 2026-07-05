#include "MLQScheduler.h"

#include "RoundRobinScheduler.h"
#include "STCFScheduler.h"
#include "../util/MetricsCalculator.h"

void MLQScheduler::run(std::vector<Process>& processes) {
    // Store pointers to split queues without copying the original processes.
    std::vector<Process*> queue1;
    std::vector<Process*> queue2;
    std::vector<Process*> queue3;

    // Assign each process to the queue specified in the input file.
    for (Process& process : processes) {
        if (process.getQueue() == 1) {
            queue1.push_back(&process);
        } else if (process.getQueue() == 2) {
            queue2.push_back(&process);
        } else if (process.getQueue() == 3) {
            queue3.push_back(&process);
        }
    }

    // currentTime is global: it is preserved from one queue to the next.
    double currentTime = 0;
    RoundRobinScheduler queue1Scheduler(2);
    RoundRobinScheduler queue2Scheduler(3);
    STCFScheduler queue3Scheduler;

    // Queues run with fixed priority: Q1, then Q2, and finally Q3.
    currentTime = queue1Scheduler.run(queue1, currentTime);
    currentTime = queue2Scheduler.run(queue2, currentTime);
    currentTime = queue3Scheduler.run(queue3, currentTime);

    MetricsCalculator::calculate(processes);
}
