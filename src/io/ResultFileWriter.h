#ifndef RESULT_FILE_WRITER_H
#define RESULT_FILE_WRITER_H

#include <string>
#include <vector>
#include "../model/Process.h"
#include "../util/MetricsCalculator.h"

class ResultFileWriter {
public:
    void write(const std::string& filePath, const std::string& inputFileName,
               const std::vector<Process>& processes, const MetricsSummary& summary) const;
};

#endif
