#include "filter_fst.hpp"

void CommentFilter::filter(std::istream& input, std::ostream& output) {
    char ch;
    while (input.get(ch))
        process(ch, output);
    finish(output);
}

void CommentFilter::process(char ch, std::ostream& output) {
    switch (ch) {
        case '\r':
        case '\n':
            process_newline(ch, output);
            break;
        case '/':
            process_slash(output);
            break;
        case '*':
            process_star(output);
            break;
        case '"':
            process_doublequote(output);
            break;
        case '\\':
            process_backslash(output);
            break;
        default:
            process_other(ch, output);
            break;
    }
}

void CommentFilter::finish(std::ostream& output) {
    if (state_ == State::AfterSlash) {
        // output that last slash we thought may be part of a comment start
        output << '/';
    }
}

void CommentFilter::process_newline(char ch, std::ostream& output) {
    bool out = true;
    switch (state_) {
        case State::Comment:
            state_ = State::Default;
            break;

        case State::AfterSlash:
            output << '/';
            state_ = State::Default;
            break;

        case State::AfterStarCommentMl:
            state_ = State::CommentMl;
            break;

        case State::AfterBackslashString:
            state_ = State::String;
            break;

        default: /* do nothing */;
    }
    if (out) output << ch;
}

void CommentFilter::process_slash(std::ostream& output) {
    bool out = true;
    switch (state_) {
        case State::Default:
            // possible comment start (if next char is "/" or "*")
            state_ = State::AfterSlash;
            out = false; // do not output just yet
            break;

        case State::AfterSlash:
            // "//" encountered, we are inside a single-line comment
            state_ = State::Comment;
            out = false;
            break;

        case State::Comment:
        case State::CommentMl:
            out = false;
            break;

        case State::AfterStarCommentMl:
            // possible multi-line comment end (if next char is "*")
            state_ = State::Default;
            out = false;
            break;

        default: /* do nothing*/;
    }
    if (out) output << '/';
}

void CommentFilter::process_star(std::ostream& output) {
    bool out = true;
    switch (state_) {
        case State::AfterSlash:
            // "/*" encountered, we are now inside a multi-line comment
            state_ = State::CommentMl;
            out = false;
            break;

        case State::Comment:
            out = false;
            break;

        case State::CommentMl:
        case State::AfterStarCommentMl:
            // possible  multi-line comment end (if next char is "/")
            state_ = State::AfterStarCommentMl;
            out = false;
            break;

        default: /* do nothing */;
    }
    if (out) output << '*';
}

void CommentFilter::process_doublequote(std::ostream& output) {
    bool out = true;
    switch (state_) {
        case State::Default:
            // we are now inside a string
            state_ = State::String;
            break;

        case State::AfterSlash:
            // prev. slash was not a part of comment start
            output << '/';
            state_ = State::String;
            break;

        case State::Comment:
        case State::CommentMl:
            out = false;
            break;

        case State::AfterStarCommentMl:
            // prev. "*" was not a part of commend end
            out = false;
            state_ = State::CommentMl;
            break;

        case State::String:
            // string was closed, we are now in default state
            state_ = State::Default;
            break;

        case State::AfterBackslashString:
            // this '"' is escaped, we are still inside a string
            state_ = State::String;
            break;

    }
    if (out) output << '"';
}

void CommentFilter::process_backslash(std::ostream& output) {
    bool out = true;
    switch (state_) {
        case State::String:
            // next char is escaped (we only care if it is '"')
            state_ = State::AfterBackslashString;
            break;

        case State::AfterBackslashString:
            // this backslash is escaped
            state_ = State::String;
            break;

        default: /* do nothing */;
    }
    if (out) output << '\\';
}

void CommentFilter::process_other(char ch, std::ostream& output) {
    bool out = true;
    switch (state_) {
        case State::AfterSlash:
            // prev. slash was not a part of comment start
            output << '/';
            state_ = State::Default;
            break;

        case State::Comment:
        case State::CommentMl:
            out = false;
            break;

        case State::AfterStarCommentMl:
            // prev. "*" was not a part of commend end
            state_ = State::CommentMl;
            out = false;
            break;

        case State::AfterBackslashString:
            state_ = State::String;
            break;

        default: /* do nothing */;
    }
    if (out) output << ch;
}
