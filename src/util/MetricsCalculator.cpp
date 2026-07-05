#include "MetricsCalculator.h"

#include <algorithm>

MetricsSummary MetricsCalculator::calculate(std::vector<Process>& processes) {
    MetricsSummary summary = {0, 0, 0, 0};

    if (processes.empty()) {
        return summary;
    }

    for (Process& process : processes) {
        // Formulas: TAT = CT - AT, WT = TAT - BT, RT = first execution - AT.
        double turnaroundTime = process.getCompletionTime() - process.getArrivalTime();
        double waitingTime = turnaroundTime - process.getBurstTime();
        double responseTime = process.getFirstStartTime() - process.getArrivalTime();

        turnaroundTime = std::max(0.0, turnaroundTime);
        waitingTime = std::max(0.0, waitingTime);
        responseTime = std::max(0.0, responseTime);

        process.setTurnaroundTime(turnaroundTime);
        process.setWaitingTime(waitingTime);
        process.setResponseTime(responseTime);

        summary.averageWaitingTime += waitingTime;
        summary.averageCompletionTime += process.getCompletionTime();
        summary.averageResponseTime += responseTime;
        summary.averageTurnaroundTime += turnaroundTime;
    }

    // Divide accumulated values by the number of processes to get averages.
    const double count = static_cast<double>(processes.size());
    summary.averageWaitingTime /= count;
    summary.averageCompletionTime /= count;
    summary.averageResponseTime /= count;
    summary.averageTurnaroundTime /= count;

    return summary;
}
