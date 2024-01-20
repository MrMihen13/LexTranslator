#pragma once

#include <string>

struct EnumStruct {
public:
	EnumStruct(const int code, const std::string string)
		: _code(code)
		, _string(string)
	{ }

	std::string toString() const {
		return _string;
	}

	int toInt() const {
		return _code;
	}

	operator int() const {
		return _code;
	}

protected:
	int _code;
	std::string _string;
};