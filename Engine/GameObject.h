#ifndef GRAPHIC_GAMEOBJECT_H
#define GRAPHIC_GAMEOBJECT_H

#include "Entity.h"
#include "Ray.h"
#include "../LowLevel/LowLevel.h"

namespace Engine {

    class GameObject: public Entity {
    private:
        static std::vector<floatType> get_angles_rot(const LowLevel::Vector<floatType>&,
                                                     const LowLevel::Vector<floatType>&) ;
    public:
        LowLevel::CoordinateSystem<floatType> local_cs;

        GameObject(const LowLevel::CoordinateSystem<floatType>& cs= LowLevel::CoordinateSystem<floatType>());
        GameObject(const LowLevel::Point<floatType>&, const LowLevel::Vector<floatType>&,
                   const LowLevel::CoordinateSystem<floatType>& cs= LowLevel::CoordinateSystem<floatType>());

        void move(const LowLevel::Vector<floatType>&);
        void planar_rotate(const std::pair<size_t, size_t>&, floatType);
        void rotate_3d(floatType, floatType, floatType);
        static LowLevel::Vector<floatType> rotate_vec3(const LowLevel::Vector<floatType>& vec,
                                                       floatType angle_x,
                                                       floatType angle_y,
                                                       floatType angle_z);
        void set_position(const LowLevel::Point<floatType>&);
        void set_direction(const LowLevel::Vector<floatType>&);

        LowLevel::Point<floatType> get_position() const;
        LowLevel::Vector<floatType> get_direction() const;
        bool get_isFixedLook() const;


        virtual floatType intersection_distance(const Ray&) const;
    };

} // Engine

#endif //GRAPHIC_GAMEOBJECT_H
