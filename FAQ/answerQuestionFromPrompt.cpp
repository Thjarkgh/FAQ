#include "answerQuestionFromPrompt.h"
#include <iostream>
#include "faqExceptions.h"

void answer_question_from_prompt(FAQ& faq) {
	std::string question;
	std::cout << "Shoot!\n";
	std::getline(std::cin, question);
	const std::string answer_text = faq.getAnswers(question);
	std::cout << answer_text << "\n";
}