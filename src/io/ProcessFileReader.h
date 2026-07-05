#ifndef PROCESS_FILE_READER_H
#define PROCESS_FILE_READER_H

#include <string>
#include <vector>
#include "../model/Process.h"

class ProcessFileReader {
public:
    std::vector<Process> read(const std::string& filePath) const;
};

#endif
