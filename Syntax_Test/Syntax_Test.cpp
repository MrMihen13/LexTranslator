#include <iostream>
#include <algorithm>

#include "../Core/lexer.h"
#include "../SYNTAX/syntax.h"
#include "../Core/command_splitter.h"

SyntaxConfig& gmconf = MathGrammarConfig;

class SyntaxLineBuilder {
public:

	size_t rfind_rule(std::string line, int ignore) {
		int posS = line.rfind('S', line.size() - 1);
		int posI = line.size() - 1;
		for (int i = 0; i <= ignore; ++i) {
			posI = line.rfind('I', posI - 1);
		}
		return std::max(posS, posI);
	}

	std::pair<std::string, std::string> buildline(SyntaxResult& result, Command& command) {
		int IDR = 10;
		
		std::stringstream ss;

		auto nodes = result.nodes;
		auto terms = command.getValueTokens();
			
		std::string line = "S";

		int ignore = 0;

		ss << line;

		while (true) {
			size_t pos = rfind_rule(line, ignore);

			if (pos == std::string::npos) {
				break;
			}
			else {
				if (line.at(pos) == 'S') {
					auto node = nodes.back();

					std::string rString = node.syntaxRule.buildRule.ruleString;

					line.replace(pos, 1, rString);
					nodes.pop_back();

					if (node.syntaxRule.code != 10) {
						ss << "\n ПРАВИЛО: " << node.syntaxRule.code <<
							"  -> " << line;
					}
				}
				else if (line.at(pos) == 'I') {
					std::string value = terms.back().value;
					line.replace(pos, 1, value);
					ss << "\n ПРАВИЛО: " << "10 [I]" << " -> " << line;
					size_t n = std::count(value.begin(), value.end(), 'I');

					ignore += n;
					terms.pop_back();
				}

			}
		}

		return std::pair<std::string, std::string>(line, ss.str());
	}

};


std::pair<bool, Command> prepare_command(std::string input) {
	Parser parser;
	auto parseResult = parser.parse(input);

	if (parseResult.isSuccess()) {
		auto commands = MathCommandSplitter()
			.split(parseResult);
		auto command = commands[0];

		return std::pair<bool, Command>(true, command);
	}
	else {
		std::cout << " - ОШИБКА ПРИ ЛЕКСИЧЕСКОМ АНАЛИЗЕ\n";
		return std::pair<bool, Command>(false, Command());
	}
}

std::pair<bool, std::string> run_syntax(Command& command) {
	Syntax syntax(gmconf);
	auto syntaxResult = syntax.proccess(command);

	for (auto& node : syntaxResult.nodes) {
		std::cout << node.syntaxRule.code << " -> " << node.syntaxRule.buildRule.ruleString << " \n";
	}

	if (syntaxResult.isSuccess()) {
		auto generated = SyntaxLineBuilder().buildline(syntaxResult, command);

		std::cout << "ПОРЯДОК РАЗБОРА:\n" << generated.second << "\n";

		return std::pair<bool, std::string>(true, generated.first);

	}
	else {
		return std::pair<bool, std::string>(false, syntaxResult.message);
	}
}

void on_result(std::string expected, std::string actual, std::string input) {
	std::cout << "ВХОДНАЯ СТРОКА:  " << input << "\n";
	std::cout << "ОЖИДАЕМЫЙ ВЫВОД: " << expected << "\n";
	std::cout << "РЕАЛЬНЫЙ ВЫВОД:  " << actual << "\n\n";

	if (expected == actual) {
		std::cout << "СТАТУС: ПРОЙДЕН\n";
	}
	else {
		std::cout << "СТАТУС: ПРОВАЛЕН\n";
	}
}

void success_1() {
	std::cout << "\nТЕСТ #1\n";
	
	std::string input = "for (a:=1;a<100;a++) do x:=a;";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = input;
	std::string actual = b_actual.second;
	
	on_result(expected, actual, input);
}


void success_2() {
	std::cout << "\nТЕСТ #2\n";
	std::string input = "arg:=I*(II+III);";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = input;
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void success_3() {
	std::cout << "\nТЕСТ #3\n";
	std::string input = "arg:=I*II+III;";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = input;
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void unclosed_bracket() {
	std::cout << "\nТЕСТ #4\n";
	std::string input = "a:=XXV-(III*x+y/(b-(I+III-VI));";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = StatusCodes::SYN_UNCLOSED_BRACKET.toString();
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void unexpected_bracket() {
	std::cout << "\nТЕСТ #5\n";

	std::string input = "a:=XXV-(III*x+y/(b-(I+III))-VI));";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = StatusCodes::SYN_UEXPECTED_BRACKET.toString();
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void runCommand(std::string line) {
	auto b_command = prepare_command(line);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string actual = b_actual.second;

	on_result(actual, actual, line);
}




int main() {
	setlocale(LC_ALL, "");

	//success_1();
	//success_2();
	//success_3();
	//unclosed_bracket();
	//unexpected_bracket();

	success_1();



	//std::string input = "a:=XXV-(III*x+y/(b-(I+III))-VI));";
	//
	//auto b_command = prepare_command(input);
	//
	//if (b_command.first != true)
	//	return -1;
	//
	//auto b_actual = run_syntax(b_command.second);
	//
	//if (b_actual.first != true) {
	//	std::cout << b_actual.second << "\n";
	//}
	//

	//success_base(input, 1);
	
	return 0;
}
