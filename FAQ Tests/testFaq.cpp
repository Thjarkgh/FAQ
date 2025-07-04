#include "pch.h"
#include "faq.h"
#include "faqExceptions.h"
#include <map>
#include <vector>
#include <string>

TEST(FAQTests, ConstructorInitializesData) {
    std::map<std::string, std::vector<std::string>> data = {
        {"What is C++?", {"A programming language."}},
        {"What is FAQ?", {"Frequently Asked Questions."}}
    };
    auto faq = FAQ(data);
    EXPECT_EQ(faq.getAnswers("What is C++?"), "\nA programming language.");
    EXPECT_EQ(faq.getAnswers("What is FAQ?"), "\nFrequently Asked Questions.");
}

TEST(FAQTests, AddEntryValid) {
    FAQ faq = FAQ();
    FAQQuestionDefinition entry = FAQQuestionDefinition("What is AI?", { "Artificial Intelligence." });
    EXPECT_NO_THROW(faq.add_question_definition(entry));
    EXPECT_EQ(faq.getAnswers("What is AI?"), "\nArtificial Intelligence.");
}

TEST(FAQTests, AddEntryQuestionTooLongThrows) {
    FAQ faq = FAQ();
    FAQQuestionDefinition entry = FAQQuestionDefinition(std::string(256, 'Q'), { "Answer" });
    EXPECT_THROW(faq.add_question_definition(entry), FAQParsingException);
}

TEST(FAQTests, AddEntryEmptyAnswersThrows) {
    FAQ faq = FAQ();
    FAQQuestionDefinition entry = FAQQuestionDefinition("Empty answers?", {});
    EXPECT_THROW(faq.add_question_definition(entry), FAQInvalidAnswersException);
}

TEST(FAQTests, AddEntryAnswerTooLongThrows) {
    FAQ faq = FAQ();
    FAQQuestionDefinition entry = FAQQuestionDefinition("Long answer?", { std::string(256, 'A') });
    EXPECT_THROW(faq.add_question_definition(entry), FAQInvalidAnswersException);
}

TEST(FAQTests, GetAnswersReturnsDefaultIfNotFound) {
    FAQ faq = FAQ();
    EXPECT_EQ(faq.getAnswers("Unknown question"), "the answer life, universe and everything is 42");
}

TEST(FAQTests, GetAnswersConcatenatesAnswers) {
    FAQ faq = FAQ();
    FAQQuestionDefinition entry = FAQQuestionDefinition("Multiple answers?", { "First", "Second", "Third" });
    faq.add_question_definition(entry);
    EXPECT_EQ(faq.getAnswers("Multiple answers?"), "\nFirst\nSecond\nThird");
}