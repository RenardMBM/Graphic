#include "GameCamera.h"

#include <cmath>

namespace Engine {
    typename GameCamera::floatType GameCamera::calcVfov(floatType fov, floatType aspect_ratio){
        return aspect_ratio * atan(fov / 2);
    }

    GameCamera::GameCamera() {
        set_property("aspect_ratio", 1);
        set_property("fov", M_PI / 3);
        set_property("vfov", calcVfov(M_PI / 3, 1));
        set_property("draw_distance", 20);
    }

    GameCamera::GameCamera(floatType fov, floatType draw_distance) {
        set_property("aspect_ratio", 1);
        set_property("fov", fov);
        set_property("vfov", calcVfov(fov, 1));
        set_property("draw_distance", draw_distance);
    }

    GameCamera::GameCamera(floatType fov, floatType vfov, floatType draw_distance) {
        set_property("aspect_ratio", 1);
        set_property("fov", fov);
        set_property("vfov", vfov);
        set_property("draw_distance", draw_distance);
    }

    GameCamera::GameCamera(floatType fov,
                           const LowLevel::Point<floatType>& look_at,
                           floatType draw_distance){
        set_property("position", LowLevel::Point<floatType>(cs.space.dim()));
        set_property("direction", cs.space.as_vector(look_at));

        set_property("direction", look_at);
        set_property("aspect_ratio", 1);
        set_property("fov", fov);
        set_property("vfov", calcVfov(fov, 1));
        set_property("draw_distance", draw_distance);
    }

    GameCamera::GameCamera(floatType fov,
                           floatType vfov,
                           const LowLevel::Point<floatType>& look_at,
                           floatType draw_distance) {
        set_property("position", LowLevel::Point<floatType>(cs.space.dim()));
        set_property("direction", cs.space.as_vector(look_at));

        set_property("direction", look_at);
        set_property("aspect_ratio", 1);
        set_property("fov", fov);
        set_property("vfov", vfov);
        set_property("draw_distance", draw_distance);
    }
} // Engine