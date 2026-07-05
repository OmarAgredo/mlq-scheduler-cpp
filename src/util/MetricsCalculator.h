#ifndef METRICS_CALCULATOR_H
#define METRICS_CALCULATOR_H

#include <vector>
#include "../model/Process.h"

struct MetricsSummary {
    double averageWaitingTime;
    double averageCompletionTime;
    double averageResponseTime;
    double averageTurnaroundTime;
};

class MetricsCalculator {
public:
    static MetricsSummary calculate(std::vector<Process>& processes);
};

#endif
