#include <istream>
#include <ostream>

// NOTE: this FST does not skip lines that contain only
// comments and whitespaces. Such feature can be implemented
// if needed with some buffering.
//
// It's able to ignore comments inside "string literals"
// (though it can't handle R"foo(  )foo").

// TODO: it's probably a good idea to remove State::After* states
// and use flags instead

class CommentFilter {
public:
    CommentFilter()
        : state_(State::Default) {}

    void filter(std::istream& input, std::ostream& output);

private:
    enum class State {
        Default,             // not in a comment or string
        AfterSlash,          // not in a comment or string, prev. char was "/"
        Comment,             // inside a single line comment
        CommentMl,           // inside a multi-line comment
        AfterStarCommentMl,  // inside a multi-line comment, prev. char was "*"
        String,              // inside a string
        AfterBackslashString // inside a string, prev. char was "\"
    };

    void process(char ch, std::ostream& output);

    void finish(std::ostream& output);

    void process_newline(char ch, std::ostream& output);
    void process_slash(std::ostream& output);
    void process_star(std::ostream& output);
    void process_doublequote(std::ostream& output);
    void process_backslash(std::ostream& output);
    void process_other(char ch, std::ostream& output);

private:
    State state_;
};
