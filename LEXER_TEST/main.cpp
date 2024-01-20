
#include "../Core/command.h"
#include "../Core/command_splitter.h"
#include "../Core/current_config.h"
#include "../Core/lexer.h"
#include "../Core/parse_item.h"
#include "../Core/parse_result.h"
#include "../Core/ref_value.h"
#include "../Core/syntax_tree_builder.h"
#include "../Core/syntax_tree_by_char_builder.h"
#include "../Core/token.h"

#include "../SYNTAX/syntax.h"


#include "../Core/operators_tree_builder.h"
#include "../Core/triads_builder.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "../Core/triadopt2.h"


class TestError {
public:
    std::string message;
    int code;
    TestError(int code, std::string message) : code(code), message(message) {}
};

class StreamUtils {
    std::stringbuf sbuf;
    std::streambuf* oldbuf;

    void update_state() {
        this->sbuf = std::stringbuf(std::ios::out);
        this->oldbuf = std::cout.rdbuf(std::addressof(this->sbuf));
    }

public:
    void capture_stream() {
        this->update_state();
    }
    bool out_stream_to_be(std::string expect) {

        std::cout.rdbuf(this->oldbuf);

        std::string output = this->sbuf.str();

        return output == expect;
    }
};



class CompareUtils {
private:
    TestError ERROR = TestError(1, "Invalid type");
public:
    template<class C1>
    void are_equal(C1 c1, C1 c2) {
        try {
            bool equal = c1 == c2;
            if (!equal) throw ERROR;
            std::cout << "Успешно";
        }
        catch (TestError& error) {
            std::cout << "Ошибка: " << error.message << "\n";
            std::cout << "Фактический результат: \n" << c1 << "\nОжидаемый результат: " << "\n" << c2 << "\n";
        }
        catch (...) {
            std::cout << "Неизвестная ошибка: \n";
            std::cout << "Фактический результат: \n" << c1 << "\nОжидаемый результат: " << "\n" << c2 << "\n";
        }
    }
};

class TestDescriptionArgs {
public:
    StreamUtils s_u = StreamUtils();
    CompareUtils c_u = CompareUtils();
};

class TestUtils {
public:
    void it(std::string testName, std::function<void(TestDescriptionArgs utils)> description) {
        std::cout << testName << ": ";
        description(TestDescriptionArgs());
        std::cout << "\n";
    }
};

class Test {
public:
    void describe(std::string testName, std::function<void(TestUtils utils)> description) {
        std::cout << "------------------ Запуск " << testName << " тестов ------------------\n";
        description(TestUtils());
        std::cout << "------------------ Тесты " << testName << " выполнены! ------------------\n";
        std::cout << "\n";
    }
};




void runParser(std::string line) {
    Parser lexer;

    auto parseResult = lexer.parse(line);

    for (auto item : parseResult.items) {
        std::cout << item << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

int main() {
    setlocale(LC_ALL, "");

    Parser lexer;

    Test t = Test();
    t.describe("White box",
        [&](TestUtils utils) {
            utils.it("Тест отработки цикла", [&](TestDescriptionArgs args) {
                std::string line = "for(i:=0;i<10;i++)do b:=10;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult{
                        Location{ 28, 0 },
                        {
                          ParseItem{Token{"for", TermTypes::FOR}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"(", TermTypes::OPEN_BRACKET}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"i", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ":=", TermTypes::ASSIGNMENT }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "10", TermTypes::NUMBER }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "i", TermTypes::IDENTIFIER }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "<", TermTypes::LESS }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "10", TermTypes::NUMBER }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "i", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "++", TermTypes::INC }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ ")", TermTypes::CLOSE_BRACKET }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "do", TermTypes::DO }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "b", TermTypes::IDENTIFIER }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ ":=", TermTypes::ASSIGNMENT }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "10", TermTypes::NUMBER }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}

                        },
                        false
                    }
                );
                });
            utils.it("Тест работы ввода числа", [&](TestDescriptionArgs args) {
                std::string line = "d:=10E;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult{
                        Location{ 9, 0 },
                        {
                          ParseItem{Token{"d", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"10E", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
                        },
                        false
                    }
                );
                });
            utils.it("Тест ввода числа логирифмического вида", [&](TestDescriptionArgs args) {
                std::string line = "b := 10.1e;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult{
                        Location{ 13, 0 },
                        {
                          ParseItem{Token{"b", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"10.1e", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
                        },
                        false
                    }
                );
                });
            utils.it("Тест работы условий", [&](TestDescriptionArgs args) {
                std::string line = "b > 10;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(7, 0),
                        {
                          ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(">", TermTypes::GREATER), StatusCodes::SUCCESS__),
                          ParseItem(Token("10", TermTypes::NUMBER), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
                        },
                        false
                        )
                );
                });
            utils.it("Тест работы декремента", [&](TestDescriptionArgs args) {
                std::string line = "a := 10--;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(11, 0),
                        {
                          ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("10", TermTypes::NUMBER), StatusCodes::SUCCESS__),
                          ParseItem(Token("--", TermTypes::DEC), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
                });
            utils.it("Тест работы присваивания", [&](TestDescriptionArgs args) {
                std::string line = "a := b := c := 0;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(19, 0),
                        {
                          ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("c", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("0", TermTypes::NUMBER), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
                });
            utils.it("Тест некорректного равенства", [&](TestDescriptionArgs args) {
                std::string line = "b=;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(4, 0),
                        {
                          ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token("=", TermTypes::UNDEFINED), StatusCodes::LEX_8),

                        },
                        true
                        )
                );
                });

            utils.it("Тест некорректного комментария", [&](TestDescriptionArgs args) {
                std::string line = "b:=10;/that's assignment?";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(8, 0),
                        {
                          ParseItem{Token{"b", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"10", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__},
                          ParseItem{Token{ "/", TermTypes::UNDEFINED }, StatusCodes::LEX_ENDLESS_COMMENT},

                        },
                        true
                        )
                );
                });
            utils.it("Тест многострочного комментария", [&](TestDescriptionArgs args) {
                std::string line = "b := 10;/*\Thats okey\n*/";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(25, 0),
                        {
                          ParseItem{Token{"b", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"10", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                        },
                        false
                    )
                );
                });
        });

    t.describe("Black box", [&](TestUtils utils) {
        utils.it("Тест отработки цикла", [&](TestDescriptionArgs args) {
            std::string line = "for(i:=0;i<10;i++)do b:=10;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult{
                    Location{ 28, 0 },
                    {
                        ParseItem{Token{"for", TermTypes::FOR}, StatusCodes::SUCCESS__},
                        ParseItem{Token{"(", TermTypes::OPEN_BRACKET}, StatusCodes::SUCCESS__},
                        ParseItem{Token{"i", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__ },
                        ParseItem{Token{ ":=", TermTypes::ASSIGNMENT }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "10", TermTypes::NUMBER }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "i", TermTypes::IDENTIFIER }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "<", TermTypes::LESS }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "10", TermTypes::NUMBER }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "i", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "++", TermTypes::INC }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ ")", TermTypes::CLOSE_BRACKET }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "do", TermTypes::DO }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "b", TermTypes::IDENTIFIER }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ ":=", TermTypes::ASSIGNMENT }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ "10", TermTypes::NUMBER }, StatusCodes::SUCCESS__},
                        ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}

                    },
                    false
            };
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест работы ввода числа", [&](TestDescriptionArgs args) {
            std::string line = "d:=1000000e;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult{
                    Location{ 13, 0 },
                    {
                      ParseItem{Token{"d", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                      ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                      ParseItem{Token{"1000000e", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                      ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                    },
                    false
            };
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест ввода числа логарифмического вида", [&](TestDescriptionArgs args) {
            std::string line = "b := 0.6666667E;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(17, 0),
                {
                  ParseItem{Token{"b", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                  ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                  ParseItem{Token{"0.6666667E", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                  ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест работы условий", [&](TestDescriptionArgs args) {
            std::string line = "b > 10;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(8, 0),
                {
                  ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(">", TermTypes::GREATER), StatusCodes::SUCCESS__),
                  ParseItem(Token("10", TermTypes::NUMBER), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
                },
                false
                );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест работы инкремента", [&](TestDescriptionArgs args) {
            std::string line = "a := 10++;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(11, 0),
                {
                  ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("10", TermTypes::NUMBER), StatusCodes::SUCCESS__),
                  ParseItem(Token("++", TermTypes::INC), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест работы присваивания", [&](TestDescriptionArgs args) {
            std::string line = "a := b := c := 0;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(18, 0),
                {
                  ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("c", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("0", TermTypes::NUMBER), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест некорректного равенства", [&](TestDescriptionArgs args) {
            std::string line = "b=;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(3, 0),
                {
                  ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token("=", TermTypes::UNDEFINED), StatusCodes::LEX_8),
                },
                true
                );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест некорректного комментария", [&](TestDescriptionArgs args) {
            std::string line = "b:=10; /Wow, Amazing";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(9, 0),
                {
                  ParseItem{Token{"b", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                  ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                  ParseItem{Token{"10", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                  ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__},
                  ParseItem{Token{ "/", TermTypes::UNDEFINED }, StatusCodes::LEX_ENDLESS_COMMENT},
                },
                true
                );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        utils.it("Тест многострочного комментария", [&](TestDescriptionArgs args) {
            std::string line = "b := 10;/*\Thats okey\n*/";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(24, 0),
                {
                  ParseItem{Token{"b", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                  ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                  ParseItem{Token{"10", TermTypes::NUMBER}, StatusCodes::SUCCESS__ },
                  ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
            });
        });
};