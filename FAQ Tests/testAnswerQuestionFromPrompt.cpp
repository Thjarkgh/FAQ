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
    std::istringstream input("What is AI?\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());
    std::ostringstream output;
    std::streambuf* origOut = std::cout.rdbuf(output.rdbuf());

    answer_question_from_prompt(faq);

    std::cin.rdbuf(orig);
    std::cout.rdbuf(origOut);

    std::string out = output.str();
    EXPECT_NE(out.find("Shoot!"), std::string::npos);
    EXPECT_NE(out.find("Artificial Intelligence"), std::string::npos);
    EXPECT_EQ(faq.getAnswersCallCount, 1);
    EXPECT_EQ(faq.lastQuestion, "What is AI?");
}

TEST(AnswerQuestionFromPromptTest, HandlesUnknownQuestion) {
    MockFAQ faq;
    std::istringstream input("Unknown question?\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());
    std::ostringstream output;
    std::streambuf* origOut = std::cout.rdbuf(output.rdbuf());

    answer_question_from_prompt(faq);

    std::cin.rdbuf(orig);
    std::cout.rdbuf(origOut);

    std::string out = output.str();
    EXPECT_NE(out.find("I don't know."), std::string::npos);
    EXPECT_EQ(faq.getAnswersCallCount, 1);
    EXPECT_EQ(faq.lastQuestion, "Unknown question?");
}
