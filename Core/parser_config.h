#pragma once

#include <map>
#include <exception>
#include <vector>
#include <iostream>

class ParserConfig {
    const int& initialState;
    const std::vector<int>& inputAlphabetMap;
    const std::vector<std::vector<int>>& statesMatrix;
    const std::vector<std::vector<int>>& boundsMatrix;
    const std::vector<std::vector<int>>& errorsMatrix;
    const std::vector<TermType>& tokenTypeMap;

public:
    ParserConfig(
        const int& initialState,
        const std::vector<int>& inputAlphabetMap,
        const std::vector<std::vector<int>>& statesMatrix,
        const std::vector<std::vector<int>>& boundsMatrix,
        const std::vector<std::vector<int>>& errorsMatrix,
        const std::vector<TermType>& tokenTypeMap
    )
        : initialState(initialState)
        , inputAlphabetMap(inputAlphabetMap)
        , statesMatrix(statesMatrix)
        , boundsMatrix(boundsMatrix)
        , errorsMatrix(errorsMatrix)
        , tokenTypeMap(tokenTypeMap)
    { }

    int getInitialState() const {
        return initialState;
    }

    int getInputAlphabetSize() const {
        return inputAlphabetMap.size();
    }

    int getCountOfStates() const {
        return statesMatrix.size();
    }

    int getCountOfInputs() const {
        return statesMatrix.at(0).size();
    }

    int getNextState(int state, int inputType) const {
        return statesMatrix.at(state).at(inputType);
    }

    int getBoundary(int state, int inputType) const {
        return boundsMatrix.at(state).at(inputType);
    }

    int getStatusCode(int state, int inputType) const {
        return errorsMatrix.at(state).at(inputType);
    }

    int mapMatrix(int arg, int state, int inputType) const {
        switch (arg) {
        case 0:
            return getNextState(state, inputType);

        case 1:
            return getBoundary(state, inputType);

        case 2:
            return getStatusCode(state, inputType);

        default:
            std::cerr << "mapMatrix invalid argument\n";
            exit(-1);
        }
    }

    int mapInputAlpha(int inputChar) const {
        int inputType = (0 <= inputChar && inputChar < getInputAlphabetSize())
            ? inputAlphabetMap.at(inputChar)
            : 0; // Any non-grammar character
        return inputType;
    }

    TermType mapTokenType(int state) const {
        TermType type = (0 <= state && state < getCountOfStates())
            ? tokenTypeMap.at(state)
            : TermTypes::UNDEFINED;
        return type;
    }
};