#include "pch.h"
#include "faq.h"
#include "answerQuestionFromPrompt.h"
#include "faqExceptions.h"
#include <sstream>

// Mock FAQ class for testing
class MockFAQ : public FAQ {
public:
    MockFAQ() : FAQ(std::map<std::string, std::vector<std::string>>{
        { "What is AI?", {"Artificial Intelligence"} },
        { "What is C++?", {"A programming language"} }
    }) {}
};

TEST(AnswerQuestionFromPromptTest, ReturnsCorrectAnswer) {
    MockFAQ faq;

    auto input = IOTestInput(std::vector<int>{}, std::vector<std::string>{ "What is AI?" });
	auto out = std::make_shared<std::string>();
	auto output = IOTestOutput(out);

    answer_question_from_prompt(
        (ProgramInput&)input,
        (ProgramOutput&)output,
        faq
    );

    EXPECT_NE(out->find("Shoot!"), std::string::npos);
    EXPECT_NE(out->find("Artificial Intelligence"), std::string::npos);
}

TEST(AnswerQuestionFromPromptTest, HandlesUnknownQuestion) {
    MockFAQ faq;

    auto input = IOTestInput(std::vector<int>{}, std::vector<std::string>{ "Unknown question?" });
    auto out = std::make_shared<std::string>();
    auto output = IOTestOutput(out);

    answer_question_from_prompt(
        (ProgramInput&)input,
        (ProgramOutput&)output,
        faq
    );

    EXPECT_NE(out->find("the answer to life, universe and everything is 42"), std::string::npos);
}
