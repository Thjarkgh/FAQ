#pragma once
#include <string>
#include "faq.h"
#include "program.h"

class FAQParser {
public:
	virtual FAQQuestionDefinition parse(const std::string& line) const = 0;
	virtual ~FAQParser() = default;
};

class FAQParserCmdline : public FAQParser {
public:
	FAQQuestionDefinition parse(const std::string& line) const override;
};

void add_question_definition_from_prompt(ProgramInput& input, ProgramOutput& output, FAQ& faq);
void add_question_definition_from_prompt(ProgramInput& input, ProgramOutput& output, FAQ& faq, const FAQParser& parser);
