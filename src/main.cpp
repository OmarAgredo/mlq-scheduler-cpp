#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "io/ProcessFileReader.h"
#include "io/ResultFileWriter.h"
#include "scheduler/MLQScheduler.h"
#include "util/MetricsCalculator.h"

namespace {
std::string getFileName(const std::string& path) {
    const std::size_t position = path.find_last_of("/\\");
    if (position == std::string::npos) {
        return path;
    }
    return path.substr(position + 1);
}

void runSimulation(const std::string& inputPath, const std::string& outputPath) {
    ProcessFileReader reader;
    ResultFileWriter writer;
    MLQScheduler scheduler;

    std::vector<Process> processes = reader.read(inputPath);
    scheduler.run(processes);
    MetricsSummary summary = MetricsCalculator::calculate(processes);
    writer.write(outputPath, getFileName(inputPath), processes, summary);

    std::cout << "Procesado: " << inputPath << " -> " << outputPath << std::endl;
}
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 3) {
            runSimulation(argv[1], argv[2]);
            return 0;
        }

        if (argc != 1) {
            std::cerr << "Uso con argumentos: " << argv[0]
                      << " inputs/mlq_custom.txt outputs/mlq_custom_output.txt" << std::endl;
            return 1;
        }

        runSimulation("inputs/mlq001.txt", "outputs/mlq001_output.txt");
        runSimulation("inputs/mlq002.txt", "outputs/mlq002_output.txt");
        runSimulation("inputs/mlq_custom.txt", "outputs/mlq_custom_output.txt");
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
