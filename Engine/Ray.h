#ifndef GRAPHIC_RAY_H
#define GRAPHIC_RAY_H
#include "../LowLevel/LowLevel.h"

namespace Engine {
    typedef long double floatType;

    class Ray {
    public:
        LowLevel::CoordinateSystem<floatType> cs;
        LowLevel::Point<floatType> pt;
        LowLevel::Vector<floatType> direction;
        Ray(const LowLevel::CoordinateSystem<floatType>&,
            const LowLevel::Point<floatType>&,
            const LowLevel::Vector<floatType>&);

        bool operator==(const Ray&) const;
        bool operator!=(const Ray&) const;

        void normalize();
    };

} // Engine

#endif //GRAPHIC_RAY_H
