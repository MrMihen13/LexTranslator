#pragma once
#include <map>
#include <string>
#include "roman.h"
#include "triad.h"

struct TableOfContants {
private:
    std::map<std::string, Triad*> values;
public:

    void saveVariable(std::string identifier, Triad* value) {
        values.insert_or_assign(identifier, value);
    }

    bool tryAssignIntTo(std::string key, int& variable) {
        const auto& valueIterator = values.find(key);

        if (valueIterator != values.end()) {
            variable = Roman::to_int(valueIterator->second->getToken()->value);
            return true;
        }

        return false;
    }
};