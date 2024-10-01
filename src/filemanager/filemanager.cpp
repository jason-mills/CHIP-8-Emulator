#include "filemanager.hpp"

bool FileManager::readFile(const std::string& path, char* memory, size_t start, size_t end){
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);

    if(file.is_open()){
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();

        // don't read into memory if the file cannot fit
        if(size > end - start) return false;

        file.seekg(0, std::ios::beg);
        file.read((memory + start), size);
        file.close();

        return true;
    }

    return false;
}
