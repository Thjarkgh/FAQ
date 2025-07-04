//
// pch.cpp
//

#include "pch.h"

IOTestInput::IOTestInput(std::vector<int> chars, std::vector<std::string> lines)
    : chars(std::move(chars)), lines(std::move(lines)) {
    chars_index = 0;
    lines_index = 0;
}

int IOTestInput::getch() {
    if (chars_index < chars.size()) {
        return chars[chars_index++];
    }
    throw std::runtime_error("No more characters to read");
}

std::string IOTestInput::getLine() {
    if (lines_index < lines.size()) {
        return lines[lines_index++];
    }
    throw std::runtime_error("No more lines to read");
}

IOTestOutput::IOTestOutput(std::shared_ptr<std::string> output) : output(std::move(output)) {}

void IOTestOutput::write(const std::string& text) {
    *output += text;
}