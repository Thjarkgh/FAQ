#pragma once
#include <string>
#include <stdexcept>

class FAQParsingException : public std::runtime_error {
public:
	FAQParsingException(const std::string& message)
		: std::runtime_error("FAQ Parsing Error: " + message) {
	}
};

class FAQInvalidAnswersException : public std::runtime_error {
public:
	FAQInvalidAnswersException(const std::string& message)
		: std::runtime_error("FAQ Invalid Answers Error: " + message) {
	}
};
