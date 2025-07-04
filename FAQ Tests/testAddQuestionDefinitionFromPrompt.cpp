#include "pch.h"
#include "AddQuestionDefinitionFromPrompt.h"
#include "faq.h"
#include "faqExceptions.h"
#include <sstream>

class FAQParserTest : public ::testing::Test {
protected:
    FAQParserCmdline parser;
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

class FAQParserMock : public FAQParser {
    public:
    FAQQuestionDefinition parse(const std::string& line) const override {
        if (line == "What is AI?\"Artificial Intelligence\"") {
            return FAQQuestionDefinition("What is AI?", { "Artificial Intelligence" });
        }
        throw FAQParsingException("Mock parsing error");
    }
};

class FAQAddEntryTest : public ::testing::Test {
protected:
    FAQParserMock parser;
    FAQ faq;
};

TEST_F(FAQAddEntryTest, AddQuestionDefinitionFromPromptAddsEntry) {
    auto input = IOTestInput(std::vector<int>{}, std::vector<std::string>{ "What is AI?\"Artificial Intelligence\"" });
    auto out = std::make_shared<std::string>();
    auto output = IOTestOutput(out);

    add_question_definition_from_prompt(
        (ProgramInput&)input,
        (ProgramOutput&)output,
        faq,
        parser
    );
    EXPECT_EQ(faq.getAnswers("What is AI?"), "\nArtificial Intelligence");
}
