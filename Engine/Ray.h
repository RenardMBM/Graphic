//
// Created by renard_liss on 27.05.2023.
//

#ifndef GRAPHIC_RAY_H
#define GRAPHIC_RAY_H
#include "../LowLevel/LowLevel.h"

namespace Engine {

    class Ray {
    private:
        using floatType = long double;
    public:
        LowLevel::CoordinateSystem<floatType> cs;
        LowLevel::Point<floatType> pt;
        LowLevel::Vector<floatType> direction;
        Ray(LowLevel::CoordinateSystem<floatType>, LowLevel::Point<floatType>, LowLevel::Vector<floatType>);
    };

} // Engine

#endif //GRAPHIC_RAY_H
