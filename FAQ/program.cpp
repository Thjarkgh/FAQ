#include <iostream>
#include <conio.h>
#include <memory>
#include <gsl/gsl>
#include "program.h"
#include "addQuestionDefinitionFromPrompt.h"
#include "answerQuestionFromPrompt.h"

int ProgramInputConsole::getch() {
	return _getch();
}

std::string ProgramInputConsole::getLine() {
	std::string line;
	std::getline(std::cin, line);
	return line;
}

void ProgramOutputConsole::write(const std::string& text) {
	std::cout << text;
}

Program::Program(std::unique_ptr<ProgramInput> in, std::unique_ptr<ProgramOutput> out)
	: input(std::move(in)), output(std::move(out)) {
	Expects(input != nullptr && output != nullptr);
}

Program Program::BuildConsoleProgram() {
	return Program(std::make_unique<ProgramInputConsole>(), std::make_unique<ProgramOutputConsole>());
}

void Program::run() {
	auto faq = FAQ();

	while (true) {
		output->write("Choose an option:\na - Add Question\nq - Ask Question\nx - Exit\n");
		int choice = input->getch();

		switch (choice)
		{
		case 'a':
			add_question_definition_from_prompt(*input, *output, faq);
			break;
		case 'q':
			answer_question_from_prompt(*input, *output, faq);
			break;
		case 'x':
			output->write("Exiting...\n");
			return;
		default:
			output->write("Invalid choice. Please try again.\n");
		}
	}
}