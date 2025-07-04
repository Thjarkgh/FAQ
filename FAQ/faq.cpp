#include "faq.h"
#include "faqExceptions.h"

FAQ::FAQ(std::map<Question, AnswerList> data)
	: faqData(std::move(data)) {
}

void FAQ::add_question_definition(const FAQQuestionDefinition& entry) {
	if (entry.question.size() > 255) {
		throw FAQParsingException("Question exceeds maximum length of 255 characters: " + entry.question);
	}
	if (entry.answers.empty()) {
		throw FAQInvalidAnswersException("Answers cannot be empty for question: " + entry.question);
	}
	for (const auto& answer : entry.answers) {
		if (answer.size() > 255) {
			throw FAQInvalidAnswersException("Answer exceeds maximum length of 255 characters: " + answer);
		}
	}

	faqData[entry.question] = entry.answers;
}

const std::string FAQ::getAnswers(const Question& question) const {
	auto it = faqData.find(question);
	if (it != faqData.end()) {
		auto line_break_fold = [](std::string a, const std::string& b)
		{
			return std::move(a) + "\n" + b;
		};
		return std::accumulate(it->second.begin(), it->second.end(), std::string(""), line_break_fold);
	}
	return "the answer life, universe and everything is 42"; // Return empty list if question not found
}
