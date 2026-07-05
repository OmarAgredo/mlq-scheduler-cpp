#include "STCFScheduler.h"

#include <algorithm>
#include <limits>

double STCFScheduler::run(std::vector<Process*>& processes, double currentTime) {
    int finished = 0;
    const int total = static_cast<int>(processes.size());

    while (finished < total) {
        Process* selected = nullptr;

        // Only arrived processes compete; choose the one with the smallest remainingTime.
        for (Process* process : processes) {
            if (!process->isFinished() && process->getArrivalTime() <= currentTime) {
                if (selected == nullptr ||
                    process->getRemainingTime() < selected->getRemainingTime() ||
                    (process->getRemainingTime() == selected->getRemainingTime() &&
                     process->getArrivalTime() < selected->getArrivalTime())) {
                    selected = process;
                }
            }
        }

        // If no process is ready, jump the clock to the next arrival.
        if (selected == nullptr) {
            double nextArrival = std::numeric_limits<double>::max();
            for (Process* process : processes) {
                if (!process->isFinished()) {
                    nextArrival = std::min(nextArrival, process->getArrivalTime());
                }
            }
            if (nextArrival == std::numeric_limits<double>::max()) {
                break;
            }
            currentTime = std::max(currentTime, nextArrival);
            continue;
        }

        // Store the first execution time to calculate response time.
        if (!selected->hasStarted()) {
            selected->setFirstStartTime(currentTime);
            selected->setStarted(true);
        }

        // Find the next arrival to allow preemption if another process appears.
        double nextArrival = std::numeric_limits<double>::max();
        for (Process* process : processes) {
            if (!process->isFinished() && process->getArrivalTime() > currentTime) {
                nextArrival = std::min(nextArrival, process->getArrivalTime());
            }
        }

        double executionTime = selected->getRemainingTime();
        if (nextArrival != std::numeric_limits<double>::max()) {
            executionTime = std::min(executionTime, nextArrival - currentTime);
        }

        selected->setRemainingTime(selected->getRemainingTime() - executionTime);
        currentTime += executionTime;

        if (selected->isFinished()) {
            selected->setRemainingTime(0);
            // When finished, store the Completion Time.
            selected->setCompletionTime(currentTime);
            ++finished;
        }
    }

    return currentTime;
}
