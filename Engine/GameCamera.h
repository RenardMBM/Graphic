#ifndef GRAPHIC_GAMECAMERA_H
#define GRAPHIC_GAMECAMERA_H

#include "GameObject.h"
#include "../LowLevel/LowLevel.h"

namespace Engine {
    class GameCamera: public GameObject {
    private:
        LowLevel::Matrix<Ray> rays_matrix = LowLevel::Matrix<Ray>(0, 0,
                                                                  Ray(cs,
                                                                      LowLevel::Point<floatType>(
                                                                              LowLevel::Vector<floatType>(
                                                                                      {0,0,0})),
                                                                      LowLevel::Vector<floatType>({1,0,0}
                                                                      ).transposed()));
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

        LowLevel::Matrix<Ray> get_rays_matrix(size_t n, size_t m);

        floatType get_aspectRatio() const;
        floatType get_fov() const;
        floatType get_vfov() const;
        size_t get_drawDistance() const;
    };

} // Engine

#endif //GRAPHIC_GAMECAMERA_H
