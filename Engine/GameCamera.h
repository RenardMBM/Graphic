#ifndef GRAPHIC_GAMECAMERA_H
#define GRAPHIC_GAMECAMERA_H

#include "GameObject.h"
#include "../LowLevel/LowLevel.h"

namespace Engine {
    class GameCamera: public GameObject {
    private:
        floatType calcVfov(floatType, floatType);
    public:
        explicit GameCamera(const LowLevel::CoordinateSystem<floatType>& cs = LowLevel::CoordinateSystem<floatType>());
        explicit GameCamera(floatType, floatType,
                   const LowLevel::CoordinateSystem<floatType>& cs = LowLevel::CoordinateSystem<floatType>());
        explicit GameCamera(floatType, floatType, floatType,
                   const LowLevel::CoordinateSystem<floatType>& cs = LowLevel::CoordinateSystem<floatType>());
        explicit GameCamera(floatType, const LowLevel::Point<floatType>& look_at, floatType,
                   const LowLevel::CoordinateSystem<floatType>& cs = LowLevel::CoordinateSystem<floatType>());
        explicit GameCamera(floatType, floatType, const LowLevel::Point<floatType>& look_at, floatType,
                            const LowLevel::CoordinateSystem<floatType>& cs = LowLevel::CoordinateSystem<floatType>());

        LowLevel::Matrix<Ray> get_rays_matrix(size_t n, size_t m) const;
    };

} // Engine

#endif //GRAPHIC_GAMECAMERA_H
