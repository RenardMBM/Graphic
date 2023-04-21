//
// Created by renard_liss on 20.04.2023.
//

#ifndef GRAPHIC_LOWLEVELEXCEPTION_H
#define GRAPHIC_LOWLEVELEXCEPTION_H
#include "./EngineException.h"

class LowLevelException: public EngineException{
    using EngineException::EngineException;
};

class ArithmeticException: public LowLevelException{
public:
    using LowLevelException::LowLevelException;

    static ArithmeticException divByZero(msgType obj){
        return ArithmeticException("attempt to divide " + obj + " by zero");
    }
};
#endif //GRAPHIC_LOWLEVELEXCEPTION_H
