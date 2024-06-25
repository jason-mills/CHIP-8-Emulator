#pragma once

#include <string>
#include <fstream>

class FileManager{
public:
    bool readFile(std::string path, char* memory, size_t start, size_t end);
};