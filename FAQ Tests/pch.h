//
// pch.h
//

#pragma once

#include <gtest/gtest.h>
#include "program.h"

// Helper to simulate user input and capture output
class IOTestInput : public ProgramInput {
private:
    int chars_index;
    std::vector<int> chars;
    int lines_index;
    std::vector<std::string> lines;

public:
    IOTestInput(std::vector<int> chars, std::vector<std::string> lines);
    int getch() override;
    std::string getLine() override;
};

class IOTestOutput : public ProgramOutput {
private:
    std::shared_ptr<std::string> output;

public:
    IOTestOutput(std::shared_ptr<std::string> output);
    void write(const std::string& text) override;
};