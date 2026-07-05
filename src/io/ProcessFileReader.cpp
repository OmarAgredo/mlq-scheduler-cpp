#include "ProcessFileReader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {
std::string trim(const std::string& text) {
    const std::string whitespace = " \t\r\n";
    const std::size_t start = text.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return "";
    }
    const std::size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}
}

std::vector<Process> ProcessFileReader::read(const std::string& filePath) const {
    std::ifstream file(filePath.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de entrada: " + filePath);
    }

    std::vector<Process> processes;
    std::string line;
    int lineNumber = 0;

    // Read the file line by line.
    while (std::getline(file, line)) {
        ++lineNumber;
        line = trim(line);

        // Ignore empty lines and comments.
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;

        // Each process field is separated by a semicolon.
        while (std::getline(ss, field, ';')) {
            fields.push_back(trim(field));
        }

        if (fields.size() != 5) {
            throw std::runtime_error("Linea invalida en " + filePath + ": " + std::to_string(lineNumber));
        }

        // Create the process with label, BT, AT, queue, and priority.
        processes.push_back(Process(
            fields[0],
            std::stod(fields[1]),
            std::stod(fields[2]),
            std::stoi(fields[3]),
            std::stoi(fields[4])
        ));
    }

    return processes;
}
