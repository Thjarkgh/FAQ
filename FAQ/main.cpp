#include <iostream>
#include <map>
#include <span>
#include <string>
#include <conio.h>
#include "AddQuestionDefinitionFromPrompt.h"
#include "answerQuestionFromPrompt.h"

int main()
{
	auto faq = FAQ();

	while (true)
	{
		std::cout << "Choose an option:\na - Add Question\nq - Ask Question\nx - Exit\n";
		int choice = _getch();

		switch (choice)
		{
			case 'a':
				add_question_definition_from_prompt(faq);
				break;
			case 'q':
				answer_question_from_prompt(faq);
				break;
			case 'x':
				std::cout << "Exiting...\n";
				return 0;
			default:
				std::cout << "Invalid choice. Please try again.\n";
		}
	}
}