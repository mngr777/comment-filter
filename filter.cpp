#include "filter.hpp"
#include <string>

// TODO: newline style detection, using file original newline instead of std::endl

void filter_comments(std::istream& input, std::ostream& output) {
    std::string line;
    bool in_ml_comment = false;
    while (std::getline(input, line)) {
        if (line.empty()) {
            // Line is empty, nothing to process
            output << std::endl;
            continue;
        }

        std::string::size_type pos = 0;
        bool done = false;
        while (!done && pos < line.size()) {
            if (!in_ml_comment) {
                // Not inside multi-line comment,
                // search for first slash
                auto slash_pos = line.find('/', pos);
                if (slash_pos == std::string::npos   // - no slashes found
                    || slash_pos + 1 == line.size()) // - slash is the last char
                {
                    // No comments left, output the rest and be done
                    output << line.substr(pos) << std::endl;
                    done = true;

                } else {
                    // Output until first slash
                    output << line.substr(pos, slash_pos - pos);

                    if (line[slash_pos + 1] == '/') {
                        // Single-line comment start, output newline and be done
                        output << std::endl;
                        done = true;

                    } else if (line[slash_pos + 1] == '*') {
                        // Multi-line comment start, advance and start searching for "*/"
                        pos = slash_pos + 1;  // advance
                        in_ml_comment = true; // we are now inside multi-line comment

                    } else {
                        // No second slash, not a comment start
                        output << '/';       // output slash
                        pos = slash_pos + 1; // advance
                    }
                }

            } else {
                // Inside multi-line comment, search for "*/"
                auto close_pos = line.find("*/", pos);
                if (close_pos == std::string::npos) {
                    done = true; // end of comment not found

                } else {
                    pos = close_pos + 2;   // advance
                    in_ml_comment = false; // not in multi-line comment anymore
                }
            }
        }
    }
}
