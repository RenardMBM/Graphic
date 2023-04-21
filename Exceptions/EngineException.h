//
// Created by renard_liss on 20.04.2023.
//

#ifndef GRAPHIC_ENGINEEXCEPTION_H
#define GRAPHIC_ENGINEEXCEPTION_H
#include <stdexcept>
#include <string>
//#include <format>
#include <utility>
#include <vector>

class EngineException:public std::exception{
protected:
    using msgType = std::string;
    msgType msg;
public:
    EngineException() = default;
    explicit EngineException(char* _s[]): msg(*_s){};
    explicit EngineException(msgType _s): msg(std::move(_s)){};

    const char* what() const noexcept override {
        return const_cast<char *>(msg.c_str());
    }
};

//class PhysicException: public EngineException{};

#endif //GRAPHIC_ENGINEEXCEPTION_H
