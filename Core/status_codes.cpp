#include "pch.h"
#include "status_codes.h"

const std::map<int, StatusCode> StatusCode::INSTANCES = {
    { StatusCodes::SUCCESS__.toInt(), StatusCodes::SUCCESS__},
    { StatusCodes::LEX_1.toInt(), StatusCodes::LEX_1 },
    { StatusCodes::LEX_2.toInt(), StatusCodes::LEX_2 },
    { StatusCodes::LEX_3.toInt(), StatusCodes::LEX_3 },
    { StatusCodes::LEX_4.toInt(), StatusCodes::LEX_4 },
    { StatusCodes::LEX_5.toInt(), StatusCodes::LEX_5 },
    { StatusCodes::LEX_6.toInt(), StatusCodes::LEX_6 },
    { StatusCodes::LEX_7.toInt(), StatusCodes::LEX_7 },
    { StatusCodes::LEX_8.toInt(), StatusCodes::LEX_8 },
    { StatusCodes::LEX_9.toInt(), StatusCodes::LEX_9 },
    { StatusCodes::LEX_10.toInt(), StatusCodes::LEX_10 },
    { StatusCodes::LEX_INVALID_INPUT_CHAR.toInt(), StatusCodes::LEX_INVALID_INPUT_CHAR},
    { StatusCodes::LEX_INVALID_OPERATOR.toInt(), StatusCodes::LEX_INVALID_OPERATOR},
    { StatusCodes::LEX_INVALID_IDENTIFIER.toInt(), StatusCodes::LEX_INVALID_IDENTIFIER},
};