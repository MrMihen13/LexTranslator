#pragma once

#include <stack>
#include <sstream>
#include <list>
#include <iomanip>

#include "../Core/stack_item.h"
#include "../Core/syntax_node.h"
#include "../Core/syntax_rule.h"
#include "../Core/command.h"
#include "../Core/status_codes.h"
#include "../Core/syntax_config.h"
#include "../Core/relations.h"


class SyntaxResult {
public:
    std::list<SyntaxNode> nodes;
    
    std::string message; 
    bool error = false;
    int tokenIndex;

    bool isSuccess() {
        return !error;
    }

    void setError(std::string message, int tokenIndex) {
        this->message = message;
        this->error = true;
        this->tokenIndex = tokenIndex;
    }
};

class Syntax {
private:
    SyntaxConfig& syntaxConfig;
    int head = 0;
    std::vector<Token> items;
    std::vector<StackItem> stack;
    std::list<SyntaxNode> nodes;
    bool error = false;

public:
    Syntax(SyntaxConfig& syntaxConfig)
        : syntaxConfig(syntaxConfig)
    { }

    int getTerminalIndex(int end) {
        for (int i = end; i >= 0; --i) {
            if (stack.at(i).isNotTerm()) {
                continue;
            }
            return i;
        }
        exit(-2);
    }

    void setup(Command command) {
        head = 0;
        stack.clear();
        nodes.clear();
        items = command.tokens;
    }

    void reduce(int input, Token token) {
        try {
            int index1 = getTerminalIndex(stack.size() - 1);
            int index2 = getTerminalIndex(index1 - 1);

            int elAt1 = stack.at(index1).code;
            int elAt2 = stack.at(index2).code;

            bool notFound = true;

            do {
                Relations innerRelation = syntaxConfig.getRelation(elAt2, elAt1);

                if (innerRelation == Relations::BASE && index2 > 0) {
                    notFound = false;
                    index1 = index2;
                    index2 = getTerminalIndex(index1 - 1);
                    elAt1 = stack.at(index1).code;
                    elAt2 = stack.at(index2).code;
                }
                else {
                    break;
                }
            } while (true);

            int baseIndex = notFound
                ? getTerminalIndex(stack.size() - 1)
                : index1;

            std::string ruleString = extractFrom(baseIndex);

            std::cout << "rule: " << ruleString << std::endl;

            SyntaxRule syntaxRule = syntaxConfig.getRuleByString(ruleString);

            SyntaxNode node = SyntaxNode(syntaxRule);

            nodes.push_back(node);
            stack.push_back(NONTERM);

        }
        catch (std::exception ex) {
            error = true;
        }
    }

    std::string extractFrom(int baseIndex) {
        std::string baseString = "";
        std::stack<std::string> revert;

        for (int i = stack.size() - 1; (i >= baseIndex || stack.back().isNotTerm()); --i) {
            revert.push(stack.back().currentChar.tokenString);
            stack.pop_back();
        }

        while (!revert.empty()) {
            baseString.append(revert.top());
            revert.pop();
        }
        return baseString;
    }

    std::string stack_str(std::vector<StackItem> stackItem) {
        std::stringstream ss;
        for (auto& el : stackItem) {
            ss << el.currentChar.tokenString;
        }
        return ss.str();
    }

    SyntaxResult proccess(Command command) {     
        setup(command);
        
        stack.push_back(START_LIMIT);
       
        SyntaxResult result;

        bool end = false;

        int tokenIndex = 0;

        do {
            tokenIndex += 1;
            Token currentToken = items[head];

            //std::cout << " #IN >> " << currentToken.value << "\n";

            int topStackTermIndex = getTerminalIndex(stack.size() - 1);

            int top = stack.at(topStackTermIndex).code;
            int input = syntaxConfig.getIndex(currentToken.type);

            Relations relation = syntaxConfig.getRelation(top, input);

#pragma region  debug
            std::cout << std::endl;

            std::cout << static_cast<char> (relation);

            std::cout << std::setw(10) << currentToken.value;

            std::cout << std::setw(10);


            for (auto item : stack) {
                std::cout << item.currentChar.tokenString << ",";
            }

            std::cout << "\n\n";
#pragma endregion 
            
            if (relation == Relations::PREV || relation == Relations::BASE) {
                shift(input, currentToken);
#pragma region  debug
                std::cout
                    << "  #AFTER SHIFT: "
                    << "\n    STACK: " << stack_str(stack) << " R[" << (char)relation << "]\n";
#pragma endregion  
                continue;
            }
            if (relation == Relations::NEXT) {
                reduce(input, currentToken);  

                if (error) {
                    result.setError(StatusCodes::SYN_EXPR_EXPECT.toString(), tokenIndex);
                    break;
                }

#pragma region  debug
                std::cout
                    << "  #AFTER REDUCE: "
                    << "\n    STACK: " << stack_str(stack) << " R[" << (char)relation << "]\n";
#pragma endregion  
                continue;
            }
            if (relation == Relations::NONE) {
                if (input == START_LIMIT.code && head != 0 && stack.size() == 2) {
                    result.error = false;
                    result.nodes = nodes;
                }
                else {
                    result.setError(syntaxConfig.getStatusCode(top, input), tokenIndex);
                }
                end = true;
                break;
            }
        } while (head < items.size());

        if (!end && !error) {
            result.setError(StatusCodes::SYN_END_OF_STATEMENT.toString(), tokenIndex);
        }

        return result;
    }

    void shift(int input, Token token) {
        stack.push_back(
            StackItem(
                syntaxConfig.getIndex(token.type),
                token.value, 
                syntaxConfig.getSyntaxChar(token.type)));
        head += 1;
    }
};

