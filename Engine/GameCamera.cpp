#include "GameCamera.h"

#include <cmath>

namespace Engine {
    floatType GameCamera::calcVfov(floatType fov, floatType aspectRatio){
        return aspectRatio * atan(fov / 2);
    }

    GameCamera::GameCamera(const LowLevel::CoordinateSystem<floatType>& cs): GameObject(cs) {
        set_property("isFixedLook", false);
        set_property("aspectRatio", 1l);
        set_property("fov", M_PI / 3);
        set_property("vfov", calcVfov(M_PI / 3, 1l));
        set_property("drawDistance", 20);
    }

    GameCamera::GameCamera(floatType fov, floatType drawDistance,
                           const LowLevel::CoordinateSystem<floatType>& cs): GameObject(cs) {
        set_property("isFixedLook", false);
        set_property("aspectRatio", 1l);
        set_property("fov", fov);
        set_property("vfov", calcVfov(fov, 1l));
        set_property("drawDistance", drawDistance);
    }

    GameCamera::GameCamera(floatType fov, floatType vfov, floatType drawDistance,
                           const LowLevel::CoordinateSystem<floatType>& cs): GameObject(cs) {
        set_property("isFixedLook", false);
        set_property("aspectRatio", 1l);
        set_property("fov", fov);
        set_property("vfov", vfov);
        set_property("drawDistance", drawDistance);
    }

    GameCamera::GameCamera(floatType fov,
                           const LowLevel::Point<floatType>& look_at,
                           floatType drawDistance,
                           const LowLevel::CoordinateSystem<floatType>& cs): GameObject(cs){
        set_property("isFixedLook", true);
        set_position(LowLevel::Point<floatType>(this->cs.space.dim()));
        set_direction(this->cs.space.as_vector(look_at));

        set_property("direction", look_at);
        set_property("aspectRatio", 1l);
        set_property("fov", fov);
        set_property("vfov", calcVfov(fov, 1l));
        set_property("drawDistance", drawDistance);
    }

    GameCamera::GameCamera(floatType fov,
                           floatType vfov,
                           const LowLevel::Point<floatType>& look_at,
                           floatType drawDistance,
                           const LowLevel::CoordinateSystem<floatType>& cs): GameObject(cs) {
        set_property("isFixedLook", true);
        set_position(LowLevel::Point<floatType>(this->cs.space.dim()));
        set_direction(this->cs.space.as_vector(look_at));

        set_property("aspectRatio", 1l);
        set_property("fov", fov);
        set_property("vfov", vfov);
        set_property("drawDistance", drawDistance);
    }
} // Engine