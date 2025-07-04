#include "pch.h"
#include "AddQuestionDefinitionFromPrompt.h"
#include "faq.h"
#include "faqExceptions.h"
#include <sstream>

class FAQParserTest : public ::testing::Test {
protected:
    FAQParser parser;
};

TEST_F(FAQParserTest, ParsesValidEntryWithOneAnswer) {
    std::string line = "What is AI?\"Artificial Intelligence\"";
    FAQQuestionDefinition entry = parser.parse(line);
    EXPECT_EQ(entry.question, "What is AI?");
    ASSERT_EQ(entry.answers.size(), 1u);
    EXPECT_EQ(entry.answers[0], "Artificial Intelligence");
}

TEST_F(FAQParserTest, ParsesValidEntryWithMultipleAnswers) {
    std::string line = "What is C++?\"A programming language\"\"Used for system programming\"";
    FAQQuestionDefinition entry = parser.parse(line);
    EXPECT_EQ(entry.question, "What is C++?");
    ASSERT_EQ(entry.answers.size(), 2u);
    EXPECT_EQ(entry.answers[0], "A programming language");
    EXPECT_EQ(entry.answers[1], "Used for system programming");
}

TEST_F(FAQParserTest, ThrowsOnMissingQuestionMark) {
    std::string line = "What is AI\"Artificial Intelligence\"";
    EXPECT_THROW(parser.parse(line), FAQParsingException);
}

TEST_F(FAQParserTest, ThrowsOnMissingOpeningQuote) {
    std::string line = "What is AI?Artificial Intelligence\"";
    EXPECT_THROW(parser.parse(line), FAQParsingException);
}

TEST_F(FAQParserTest, ThrowsOnMissingClosingQuote) {
    std::string line = "What is AI?\"Artificial Intelligence";
    EXPECT_THROW(parser.parse(line), FAQParsingException);
}

class FAQAddEntryTest : public ::testing::Test {
protected:
    FAQParser parser;
    FAQ faq;
};

TEST_F(FAQAddEntryTest, AddQuestionDefinitionFromPromptAddsEntry) {
    std::istringstream input("What is AI?\"Artificial Intelligence\"\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());
    add_question_definition_from_prompt(faq, parser);
    std::cin.rdbuf(orig);
    EXPECT_EQ(faq.getAnswers("What is AI?"), "\nArtificial Intelligence");
}
