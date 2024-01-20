#pragma once

#include "transition_info.h"
#include "current_config.h"

class StateMachine {
protected:
    const ParserConfig& SmConfig;

    static const int IS_BOUNDARY_CODE = 1;
public:
    StateMachine(const ParserConfig& smConfig)
        : SmConfig(smConfig)
        , currentState(smConfig.getInitialState())
    { }

    int currentState = 1;

    TransitionInfo getTransition(char inputChar) {
        int inputType = SmConfig.mapInputAlpha(inputChar);
        int nextState = SmConfig.getNextState(currentState, inputType);
        bool isBoundary = SmConfig.getBoundary(currentState, inputType) == IS_BOUNDARY_CODE;
        StatusCode statusCode = SmConfig.getStatusCode(currentState, inputType);

        return TransitionInfo(inputChar, inputType, nextState, isBoundary, statusCode);
    }

    int getInitialState() {
        return SmConfig.getInitialState();
    }

    void reset() {
        currentState = SmConfig.getInitialState();
    }
};