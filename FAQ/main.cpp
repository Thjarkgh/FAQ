#include "program.h"

int main() {
	auto program = Program::BuildConsoleProgram();
	program.run();
	return 0;
}