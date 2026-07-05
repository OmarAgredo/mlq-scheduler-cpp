#include "ResultFileWriter.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::string formatNumber(double value) {
    std::ostringstream out;
    if (value == static_cast<long long>(value)) {
        out << static_cast<long long>(value);
    } else {
        out << std::fixed << std::setprecision(2) << value;
    }
    return out.str();
}
}

void ResultFileWriter::write(const std::string& filePath, const std::string& inputFileName,
                             const std::vector<Process>& processes, const MetricsSummary& summary) const {
    std::ofstream file(filePath.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de salida: " + filePath);
    }

    // Output file header.
    file << "# archivo: " << inputFileName << "\n";
    file << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

    // Write one line per process with original data and calculated metrics.
    for (const Process& process : processes) {
        file << process.getLabel() << ';'
             << formatNumber(process.getBurstTime()) << ';'
             << formatNumber(process.getArrivalTime()) << ';'
             << process.getQueue() << ';'
             << process.getPriority() << ';'
             << formatNumber(process.getWaitingTime()) << ';'
             << formatNumber(process.getCompletionTime()) << ';'
             << formatNumber(process.getResponseTime()) << ';'
             << formatNumber(process.getTurnaroundTime()) << "\n";
    }

    // Write the overall averages at the end.
    file << "# WT=" << formatNumber(summary.averageWaitingTime)
         << "; CT=" << formatNumber(summary.averageCompletionTime)
         << "; RT=" << formatNumber(summary.averageResponseTime)
         << "; TAT=" << formatNumber(summary.averageTurnaroundTime)
         << ";\n";
}
