#pragma once
#include <map>
#include <vector>
#include <string>
#include <execution>

typedef std::vector<std::string> AnswerList;
typedef std::string Question;

struct FAQQuestionDefinition
{
	const Question question;
	const AnswerList answers;

	FAQQuestionDefinition(const Question& q, const AnswerList& a)
		: question(q), answers(a) {
	}
};

class FAQ
{
private:
	std::map<Question, AnswerList> faqData;

public:
	FAQ(std::map<Question, AnswerList> data = {});
	virtual ~FAQ() = default;

	void add_question_definition(const FAQQuestionDefinition& entry);

	// Note: This method is virtual to allow mocking in tests without gmock. => TODO
	virtual const std::string getAnswers(const Question& question) const;
};
