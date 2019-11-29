#include <iostream> // input/output

// I haven't actually /** build // **/ this code.
// It's just an input file for testing some /* weird */ cases

// The Main Function
int main(int argc /* # of arguments*/, char** argv /* argument values */) {
    /*
      The following is usually referred to as "chevron hell"
     */
    std::cout << "To add a single-line comment use \"//\". "
              << "It will comment out everyting until the end of line. Like this: "
              << "`int x = 5; // definition and initialization of \"x\" variable.`"
              << std::endl;
    std::cout << "If you want to add a comment that spans multiple lines use \"/*\" and \"*/\""
              << "That's what it looks like:" << std::endl
              << "<code>" << std::endl
              << "/* This class is a common ancestor of"
              <<     "all widgets used in out application. */"
              << "class WidgetBase {};"
              << "</code>" << std::endl;

    for (int i = 0 /* init **/; i < argc /** condition */; ++i /** update **/) // for loop
        std::cout << "argument " << i << ": " << argv[i] << std::endl;
    return 0;
}

// Trailing slash should be printed even if it's an error, see filter_fst.cpp
o/
