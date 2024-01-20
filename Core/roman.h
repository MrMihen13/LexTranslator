#pragma once

#include <string>
#include <map>

struct Roman
{
    static std::string to_roman(unsigned int value)
    {
        struct romandata_t { unsigned int value; char const* numeral; };

        const struct romandata_t romandata[] =
        {
            { 1000, "M"}, {900, "CM"},
            { 500, "D"}, {400, "CD"},
            { 100, "C"}, { 90, "XC"},
            { 50, "L"}, { 40, "XL"},
            { 10, "X"}, { 9, "IX"},
            { 5, "V"}, { 4, "IV"},
            { 1, "I"},
            { 0, NULL} // end marker
        };

        std::string result;
        for (const romandata_t* current = romandata; current->value > 0; ++current)
        {
            while (value >= current->value)
            {
                result += current->numeral;
                value -= current->value;
            }
        }
        return result;
    }

    static int to_int(std::string roman) {
        int res = 0;

        std::map<char, int> values = {
            { 'I', 1},
            { 'V', 5},
            { 'X', 10 },
            { 'L', 50 },
            { 'C', 100 },
            { 'D', 500 },
            { 'M', 1000 }
        };

        std::string digits = "IVXLCDM";

        for (int q = 0; q < roman.size() - 1; ++q) {
            if (digits.find_first_of(roman[q]) < digits.find_first_of(roman[q + 1])) {
                res -= values[roman[q]];
            }
            else {
                res += values[roman[q]];
            }
        }

        return res + values[roman[roman.size() - 1]];
    }
};