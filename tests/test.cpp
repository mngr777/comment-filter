#include <iostream>

// Prints command line arguments
int main(int argc, char** argv) {

    /**
       Here's a multi-line comment
       for testing purposes
     */

    std::cout << "Comments /* like this */ are removed from strings by filter_comments()"
              << std::endl;

    int x = 5; // declare and initialize `x';

    for (int i = 0 /* init **/; i < argc /** condition */; ++i /** update **/)
        std::cout << "argument " << i << ": " << argv[i];
    return 0;
}
