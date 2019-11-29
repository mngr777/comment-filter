There are 2 implementations of comment filtering in (1) filter.* and (2) filter_fst.*.

(1) Implements the task as requested, uses std::endl for printing newline chars.
    Should work correctly on `tests/test.cpp'

(2) Additionally handles string literals, except for (in general) R"foo(...)foo".
    Preserves original newline symbols.
    Test input files: `tests/test_fst.cpp', `tests/test_fst_dos.cpp'
    and `tests/test_fst_mac.cpp'.

Usage:
$ ./test [<input-filename>[ output_filename]]
$ ./test_fst [<input-filename>[ output_filename]]

Examples *nix (./test and ./test_fst have the same interface):
$ ./test input.cpp
$ ./test input.cpp output.cpp
$ cat input.cpp | ./test - output.cpp
$ cat input.cpp | ./test | grep pattern
