#ifndef GRAPHIC_GAMEOBJECT_H
#define GRAPHIC_GAMEOBJECT_H

#include "Entity.h"
#include "../LowLevel/LowLevel.h"

namespace Engine {

    class GameObject: public Entity {
    public:
        GameObject(const LowLevel::CoordinateSystem<floatType>& cs= LowLevel::CoordinateSystem<floatType>());
        GameObject(const LowLevel::Point<floatType>&, const LowLevel::Vector<floatType>&,
                const LowLevel::CoordinateSystem<floatType>& cs= LowLevel::CoordinateSystem<floatType>());

        void move(const LowLevel::Vector<floatType>&);
        void planar_rotate(const std::pair<size_t, size_t>&, floatType);
        void rotate_3d(floatType, floatType, floatType);
        void set_position(const LowLevel::Point<floatType>&);
        void set_direction(const LowLevel::Vector<floatType>&);
    };

} // Engine

#endif //GRAPHIC_GAMEOBJECT_H
