#include "answerQuestionFromPrompt.h"

void answer_question_from_prompt(ProgramInput& input, ProgramOutput& output, FAQ& faq) {
	output.write("Shoot!\n");
	std::string question = input.getLine();
	const std::string answer_text = faq.getAnswers(question);
	output.write(answer_text + "\n");
}