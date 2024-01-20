#pragma once
#include <map>
#include "triad.h"
#include <string>

struct TableOfVars {
private:
    std::map<std::string, Triad*> values;
public:

    void saveVariable(std::string identifier, Triad* value) {
        values.insert_or_assign(identifier, value);
    }

    bool tryGetDep(std::string key, int& variable) {
        const auto& valueIterator = values.find(key);

        if (valueIterator != values.end()) {
            variable = valueIterator->second->dep;
            return true;
        }

        return false;
    }
};