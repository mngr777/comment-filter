#include <fstream>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "filter_fst.hpp"

int main(int argc, char** argv) {
    const std::string filename_default("-");

    // Get input stream
    std::istream *input = &std::cin;
    std::fstream input_file;
    if (argc > 1 && filename_default != argv[1]) {
        input_file = open(argv[1]);
        input = &input_file;
    }

    // Get output stream
    std::ostream *output = &std::cout;
    std::fstream output_file;
    if (argc > 2 && filename_default != argv[2]) {
        output_file = open(argv[2], std::ios_base::out);
        output = &output_file;
    }

    // Filter
    CommentFilter filter;
    filter.filter(*input, *output);

    return 0;
}
