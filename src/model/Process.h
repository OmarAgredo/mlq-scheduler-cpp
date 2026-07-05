#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
private:
    std::string label;
    double burstTime;
    double remainingTime;
    double arrivalTime;
    int queue;
    int priority;
    double firstStartTime;
    double completionTime;
    double waitingTime;
    double responseTime;
    double turnaroundTime;
    bool started;

public:
    Process(const std::string& label, double burstTime, double arrivalTime, int queue, int priority);

    const std::string& getLabel() const;
    double getBurstTime() const;
    double getRemainingTime() const;
    double getArrivalTime() const;
    int getQueue() const;
    int getPriority() const;
    double getFirstStartTime() const;
    double getCompletionTime() const;
    double getWaitingTime() const;
    double getResponseTime() const;
    double getTurnaroundTime() const;
    bool hasStarted() const;
    bool isFinished() const;

    void setRemainingTime(double remainingTime);
    void setFirstStartTime(double firstStartTime);
    void setCompletionTime(double completionTime);
    void setWaitingTime(double waitingTime);
    void setResponseTime(double responseTime);
    void setTurnaroundTime(double turnaroundTime);
    void setStarted(bool started);
};

#endif
