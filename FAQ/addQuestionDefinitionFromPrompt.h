#pragma once
#include <string>
#include <memory>
#include "faq.h"

class FAQParser
{
public:
	FAQQuestionDefinition parse(const std::string& line) const;
};

void add_question_definition_from_prompt(FAQ& faq, FAQParser parser = FAQParser());
