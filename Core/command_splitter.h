#pragma once

#include <vector>

#include "parse_result.h"
#include "command.h"

class MathCommandSplitter {
public:
    std::vector<Command> split(ParseResult& parseResult) {
        int index = 0;

        std::vector<Command> commands;

        while (index < parseResult.items.size()) {
            Command command;
            
            while (index < parseResult.items.size()) {
                ParseItem item = parseResult.items[index];
                
                if (!item.isValid()) {
                    command.isValid = false;
                }

                command.tokens.push_back(item.token);

                // TODO: add list of value-types
                if (item.token.type == TermTypes::NUMBER || item.token.type == TermTypes::IDENTIFIER) {
                    command.values.push_back(item.token);
                }
                
                index += 1;
            }

            command.tokens.push_back(Token("Ê", TermTypes::LIMIT));
            commands.push_back(command);
        }
        return commands;
    }
};