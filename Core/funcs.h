#pragma once

#include <string>
#include <vector>

class Funcs {
public:
    template <class T>
    static std::string join(std::vector<T> items, std::string delim = "") {
        std::ostringstream imploded;
        std::copy(items.begin(), items.end(),
            std::ostream_iterator<std::string>(imploded, delim.c_str()));
        return  imploded.str();
    }
};
