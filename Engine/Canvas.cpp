#include "Canvas.h"

namespace Engine {
    Canvas::Canvas(const size_t& n, const size_t& m): n(n),
                                                      m(m),
                                                      distances(n, m, -1),
                                                      mask(n, m, false){}

    void Canvas::draw(){
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                if (mask[i][j]) {
                    // TODO draw i, j
                }
            }
        }
    }
    void Canvas::update(GameCamera& camera,
                        const std::vector<std::shared_ptr<GameObject>>& objs) const{
        LowLevel::Matrix<Ray> rays_mat = camera.get_rays_matrix(n, m);

        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++j){
                if (mask[i][j]) continue;

                Ray ray = rays_mat[i][j];
                for (const auto& obj: objs){
                    floatType dist = obj->intersection_distance(ray);
                    if (distances[i][j] < 0 || dist < distances[i][j]) {
                        distances[i][j] = dist;
                        if (dist < camera.get_drawDistance() * ray.direction.length()){
                            mask[i][j] = true;
                        }
                    }
                }
            }
        }

    }
} // BaseGame