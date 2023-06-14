//
// Created by renard_liss on 27.05.2023.
//

#include "Ray.h"

namespace Engine {
    Ray::Ray(const LowLevel::CoordinateSystem<floatType>& cs,
             const LowLevel::Point<floatType>& pt,
             const LowLevel::Vector<floatType>& direction): cs(cs), pt(pt), direction(direction) {
        if (this->direction.isTransposed) this->direction.transpose();
    }

    bool Ray::operator==(const Ray &other) const {
        return (this->pt == other.pt &&
                this->cs == other.cs &&
                this->direction == other.direction);
    }

    bool Ray::operator!=(const Ray &other) const {
        return !(this->operator==(other));
    }

    void Ray::normalize() {
        this->direction = this->direction.normalize();
    }
} // Engine