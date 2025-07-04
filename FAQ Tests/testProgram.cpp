// Acceptance Test
#include "pch.h"
TEST(ProgramTest, AcceptanceTest) {
    auto input_chars = std::vector<int>{ 'a', 'q', 'q', 'x' };
    auto input_lines = std::vector<std::string>{
        "What is Peters favorite food? \"Pizza\" \"Spaghetti\" \"Ice cream\"",
        "What is Peters favorite food?",
        "When is Peters birthday?"
    };

	auto output_string = std::make_shared<std::string>();
    auto program = Program(
        std::make_unique<IOTestInput>(input_chars, input_lines),
        std::make_unique<IOTestOutput>(output_string)
    );

	program.run();

    EXPECT_NE(output_string->find("\nPizza\nSpaghetti\nIce cream\n"), std::string::npos);
	EXPECT_NE(output_string->find("the answer to life, universe and everything is 42"), std::string::npos);
}