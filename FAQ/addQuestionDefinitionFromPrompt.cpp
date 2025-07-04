#include "AddQuestionDefinitionFromPrompt.h"
#include "faqExceptions.h"

FAQQuestionDefinition FAQParserCmdline::parse(const std::string& line) const {
	size_t questionEnd = line.find('?');
	if (questionEnd == std::string::npos) {
		throw FAQParsingException("Invalid FAQ entry format");
	}

	std::string question = line.substr(0, questionEnd + 1);
	std::vector<std::string> answers;

	size_t end = questionEnd;
	while (end + 1 < line.size()) {
		size_t start = line.find('"', end + 1);
		if (start == std::string::npos) {
			break; // No more answers found
		}
		if (start + 1 >= line.size()) {
			throw FAQParsingException("Invalid FAQ entry format: missing closing quote (last character is \")");
		}
		end = line.find('"', start + 1);
		if (end == std::string::npos) {
			throw FAQParsingException("Invalid FAQ entry format: missing closing quote");
		}

		answers.push_back(line.substr(start + 1, end - start - 1));
	}
	return FAQQuestionDefinition(std::move(question), answers);
}

void add_question_definition_from_prompt(ProgramInput& input, ProgramOutput& output, FAQ& faq) {
	FAQParserCmdline parser = FAQParserCmdline();
	add_question_definition_from_prompt(input, output, faq, parser);
}

void add_question_definition_from_prompt(ProgramInput& input, ProgramOutput& output, FAQ& faq, const FAQParser& parser) {
	try {
		output.write("Enter new question and answers in the format: <question>? \"<answer1>\" \"<answer2>\" \"<answerX>\"\n");
		std::string input_str = input.getLine();
		const FAQQuestionDefinition parsed = parser.parse(input_str);
		faq.add_question_definition(parsed);
		output.write("Question added.\n");
	}
	catch (const FAQParsingException& e) {
		std::cerr << "Error parsing question: " << e.what() << "\n";
	}
	catch (const FAQInvalidAnswersException& e) {
		std::cerr << "Error with answers: " << e.what() << "\n";
	}
}
