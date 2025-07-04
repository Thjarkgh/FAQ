#pragma once
#include <string>
#include <memory>
#include <iostream>

class ProgramInput {
public:
	virtual int getch() = 0;
	virtual std::string getLine() = 0;
	virtual ~ProgramInput() = default;
};

class ProgramOutput {
public:
	virtual void write(const std::string& text) = 0;
	virtual ~ProgramOutput() = default;
};

class ProgramInputConsole : public ProgramInput {
public:
	int getch() override;
	std::string getLine() override;
};

class ProgramOutputConsole : public ProgramOutput {
public:
	void write(const std::string& text) override;
};

class Program {
private:
	std::unique_ptr<ProgramInput> input;
	std::unique_ptr<ProgramOutput> output;

public:
	Program(std::unique_ptr<ProgramInput> input, std::unique_ptr<ProgramOutput> output);
	
	static Program BuildConsoleProgram();

	void run();
};