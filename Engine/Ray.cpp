//
// Created by renard_liss on 27.05.2023.
//

#include "Ray.h"

namespace Engine {
    Ray::Ray(LowLevel::CoordinateSystem<Engine::Ray::floatType> cs,
             LowLevel::Point<Engine::Ray::floatType> pt,
             LowLevel::Vector<Engine::Ray::floatType> direction): cs(cs), pt(pt), direction(direction) {}
} // Engine