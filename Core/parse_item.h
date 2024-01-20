#pragma once

#include "status_codes.h"
#include "token.h"

struct ParseItem {
    Token token;
    StatusCode statusCode;

    bool isValid() {
        return statusCode == StatusCodes::SUCCESS__;
    }

    ParseItem(Token token, StatusCode statusCode = StatusCodes::SUCCESS__)
        : token(token), statusCode(statusCode)
    {
    }

    friend std::ostream& operator<<(std::ostream& s, const ParseItem& parseItem)
    {
        s << "{" << "status code: " << parseItem.statusCode.toString() << ", token: " << parseItem.token << "}";
        return s;
    }

    bool operator==(const ParseItem& target) {
        return target.token == this->token && target.statusCode.toString() == this->statusCode.toString();
    }

    bool operator!=(const ParseItem& target) {
        return target.token != this->token && target.statusCode != this->statusCode;
    }
};
