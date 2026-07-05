#include "RoundRobinScheduler.h"

#include <algorithm>
#include <limits>
#include <queue>

RoundRobinScheduler::RoundRobinScheduler(double quantum) : quantum(quantum) {
}

double RoundRobinScheduler::run(std::vector<Process*>& processes, double currentTime) {
    if (processes.empty()) {
        return currentTime;
    }

    std::sort(processes.begin(), processes.end(), [](Process* a, Process* b) {
        if (a->getArrivalTime() == b->getArrivalTime()) {
            return a->getLabel() < b->getLabel();
        }
        return a->getArrivalTime() < b->getArrivalTime();
    });

    std::queue<int> readyQueue;
    std::vector<bool> added(processes.size(), false);
    int finished = 0;

    // Add processes that have already arrived to the ready queue.
    auto addArrivedProcesses = [&]() {
        for (int i = 0; i < static_cast<int>(processes.size()); ++i) {
            if (!added[i] && !processes[i]->isFinished() && processes[i]->getArrivalTime() <= currentTime) {
                readyQueue.push(i);
                added[i] = true;
            }
        }
    };

    while (finished < static_cast<int>(processes.size())) {
        addArrivedProcesses();

        // If no process is ready, advance time to the next arrival.
        if (readyQueue.empty()) {
            double nextArrival = std::numeric_limits<double>::max();
            for (int i = 0; i < static_cast<int>(processes.size()); ++i) {
                if (!added[i] && !processes[i]->isFinished()) {
                    nextArrival = std::min(nextArrival, processes[i]->getArrivalTime());
                }
            }
            if (nextArrival == std::numeric_limits<double>::max()) {
                break;
            }
            currentTime = std::max(currentTime, nextArrival);
            addArrivedProcesses();
        }

        int index = readyQueue.front();
        readyQueue.pop();
        Process* process = processes[index];

        // Store the first time the process gets CPU time to calculate RT.
        if (!process->hasStarted()) {
            process->setFirstStartTime(currentTime);
            process->setStarted(true);
        }

        // Run for at most one quantum or the remaining process time.
        double executionTime = std::min(quantum, process->getRemainingTime());
        process->setRemainingTime(process->getRemainingTime() - executionTime);
        currentTime += executionTime;

        addArrivedProcesses();

        if (process->isFinished()) {
            process->setRemainingTime(0);
            // When finished, store the process completion time.
            process->setCompletionTime(currentTime);
            ++finished;
        } else {
            // If it did not finish, move it to the back of the Round Robin queue.
            readyQueue.push(index);
        }
    }

    return currentTime;
}
