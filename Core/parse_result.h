#pragma once

#include "token.h"
#include "term_type.h"
#include "parse_item.h"

#include <vector>

struct Location {
    int index = 0;
    int tokenIndex = 0;
    Location() {};
    Location(int index, int tokenIndex) : index(index), tokenIndex(tokenIndex) {}
    bool operator==(const Location& target) {
        return target.index == this->index && target.tokenIndex == this->tokenIndex;
    }
    friend std::ostream& operator<<(std::ostream& s, const Location& parseItem) {
        s << "{ index: " << parseItem.index << ", tokenIndex: " << parseItem.tokenIndex << "}\n";
        return s;
    }
};


struct ParseResult {
private:
    bool error = false;
public:
    ParseResult() {};

    ParseResult(Location location, std::vector<ParseItem> items, bool error) : current(location), items(items), error(error) {};

    std::vector<ParseItem> items;
    Location current;

    void addError(std::string value, StatusCode statusCode) {
        items.push_back(ParseItem(Token(value, TermTypes::UNDEFINED), statusCode));
        error = true;
    }

    bool isSuccess() {
        return !error;
    }

    void add(Token token) {
        items.push_back(ParseItem(token));
    }

    void add(std::string value, TermType tokenType) {
        items.push_back(ParseItem(Token(value, tokenType)));
    }

    bool operator==(const ParseResult& target) {
        if (target.items.size() != this->items.size()) return false;
        for (int i = 0; i < target.items.size(); i++) {
            if (this->items[i] != target.items[i]) return false;
        };
        return this->current == target.current && this->error == target.error;
    }

    friend std::ostream& operator<<(std::ostream& s, const ParseResult& parseItem)
    {
        s << "{\n" << "current: " << parseItem.current << "error: " << parseItem.error << "\nitems: [";
        for (auto& item : parseItem.items) {
            s << item << ",\n";
        }
        s << "]\n}";
        return s;
    }
};
