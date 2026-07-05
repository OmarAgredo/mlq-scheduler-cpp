#include "Process.h"

Process::Process(const std::string& label, double burstTime, double arrivalTime, int queue, int priority)
    : label(label),
      burstTime(burstTime),
      remainingTime(burstTime),
      arrivalTime(arrivalTime),
      queue(queue),
      priority(priority),
      firstStartTime(-1),
      completionTime(0),
      waitingTime(0),
      responseTime(0),
      turnaroundTime(0),
      started(false) {
}

const std::string& Process::getLabel() const { return label; }
double Process::getBurstTime() const { return burstTime; }
double Process::getRemainingTime() const { return remainingTime; }
double Process::getArrivalTime() const { return arrivalTime; }
int Process::getQueue() const { return queue; }
int Process::getPriority() const { return priority; }
double Process::getFirstStartTime() const { return firstStartTime; }
double Process::getCompletionTime() const { return completionTime; }
double Process::getWaitingTime() const { return waitingTime; }
double Process::getResponseTime() const { return responseTime; }
double Process::getTurnaroundTime() const { return turnaroundTime; }
bool Process::hasStarted() const { return started; }
bool Process::isFinished() const { return remainingTime <= 0; }

void Process::setRemainingTime(double remainingTime) { this->remainingTime = remainingTime; }
void Process::setFirstStartTime(double firstStartTime) { this->firstStartTime = firstStartTime; }
void Process::setCompletionTime(double completionTime) { this->completionTime = completionTime; }
void Process::setWaitingTime(double waitingTime) { this->waitingTime = waitingTime; }
void Process::setResponseTime(double responseTime) { this->responseTime = responseTime; }
void Process::setTurnaroundTime(double turnaroundTime) { this->turnaroundTime = turnaroundTime; }
void Process::setStarted(bool started) { this->started = started; }
