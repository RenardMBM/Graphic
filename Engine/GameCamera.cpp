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


    floatType GameCamera::get_aspectRatio() const{
        return std::any_cast<floatType>(get_property("aspectRatio"));
    }
    floatType GameCamera::get_fov() const{
        return std::any_cast<floatType>(get_property("fov"));
    }
    floatType GameCamera::get_vfov() const{
        return std::any_cast<floatType>(get_property("vfov"));
    }
    size_t GameCamera::get_drawDistance() const{
        return std::any_cast<size_t>(get_property("drawDistance"));
    }

    LowLevel::Matrix<Ray> GameCamera::get_rays_matrix(size_t n, size_t m) const{ // n - height, m - width
        LowLevel::Matrix<Ray> mat(n, m,
                                  Ray(cs,
                                      get_position(),
                                      LowLevel::Vector<floatType>({1,0,0}).transposed()));

        auto alpha = get_vfov(),
             beta = get_fov();
        floatType d_alpha = alpha / (floatType)m, d_beta = beta / (floatType)n,
                h_alpha = alpha / 2, h_beta = beta / 2, alpha_j, beta_i;

        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++j){
                alpha_j = d_alpha * (floatType)j - h_alpha;
                beta_i = d_beta * (floatType)i - h_beta;

                LowLevel::Vector<floatType> v({1,0,0}); v.transpose();

                LowLevel::Vector<floatType> n_dir = rotate_vec3(
                                v,
                                0,
                                alpha_j,
                                beta_i);

                mat[i][j].direction = cs.space.as_vector(
                        LowLevel::Point<floatType>(n_dir /(v % n_dir)));
            }
        }
        return mat;
    }

} // Engine