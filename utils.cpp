#include "utils.hpp"
#include <iostream>
#include <cstdlib>

void exit_error(const std::string& message) {
    std::cerr << message << std::endl;
    std::exit(EXIT_FAILURE);
}

std::fstream open(
    const std::string& filename,
    std::ios_base::openmode mode)
{
    std::fstream file(filename, mode);
    if (!file)
        exit_error(std::string("Failed to open file `") + filename + "'");
    return file;
}
