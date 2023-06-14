#include "GameObject.h"

namespace Engine {
// region constructors
    std::vector<floatType> GameObject::get_angles_rot(const LowLevel::Vector<floatType>& vec1,
                                                      const LowLevel::Vector<floatType>& vec2) {
        if (vec1.size() != vec2.size()) throw std::exception(); // "size of vectors must be equal"
        std::vector<floatType> angles(vec1.size());

        LowLevel::Vector<floatType> v1(vec1.normalize()), v2(vec2.normalize());
        if (v1.isTransposed) v1.transpose();
        if (v2.isTransposed) v2.transpose();
        LowLevel::Vector<floatType> dv = v1 - v2;
        LowLevel::Vector<floatType> tmp;

        for (size_t i = 0; i < dv.size(); ++i){
            tmp = v1;
            tmp[i] += dv[i];
            angles[i] = acos(v1 % tmp.normalize());
        }

        return angles;
    }

    GameObject::GameObject(const LowLevel::CoordinateSystem<floatType>& cs): Entity(cs){
        this->local_cs = LowLevel::CoordinateSystem<floatType>();
        set_property("isFixedLook", false);
        set_position(LowLevel::Point<floatType>(cs.space.dim()));
        set_direction(LowLevel::Vector<floatType>(cs.space.dim(), 1l));
    }
    GameObject::GameObject(const LowLevel::Point<floatType> &pos,
                           const LowLevel::Vector<floatType>& dir,
                           const LowLevel::CoordinateSystem<floatType>& cs): Entity(cs){
        if (pos.size() != dir.size() || pos.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        this->local_cs = LowLevel::CoordinateSystem<floatType>();
        set_property("isFixedLook", false);
        LowLevel::Vector<floatType> f_dir(dir);

        if (f_dir.isTransposed) f_dir.transpose();

        set_position(pos);
        set_direction(f_dir);

    }
// endregion

// region methods
    void GameObject::move(const LowLevel::Vector<floatType>& vec){
        if (vec.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        bool isFixedLook = std::any_cast<bool>(get_property("isFixedLook"));
        if (isFixedLook) {
            auto dir = std::any_cast<LowLevel::Vector<floatType>>(get_property("direction"));
            set_direction(dir - vec);
        }
        set_position(std::any_cast<LowLevel::Point<floatType>>(get_property("position")) + vec);
    }
    void GameObject::planar_rotate(const std::pair<size_t, size_t>& inds, floatType angle){
        if (inds.first >= cs.space.dim() || inds.second >= cs.space.dim()) throw std::range_error("indexes must be less dim");
        auto dir = std::any_cast<LowLevel::Vector<floatType>>(get_property("direction"));
        if (!dir.isTransposed) dir.transpose();
        LowLevel::Matrix<floatType> rot_mat = LowLevel::Matrix<floatType>::rotation_matrix(inds,
                                                                                           angle,
                                                                                           dir.size());
        LowLevel::Vector<floatType> n_dir = dir * rot_mat;
        if (n_dir.isTransposed) n_dir.transpose();
        set_direction(n_dir);
    }
    void GameObject::rotate_3d(floatType angle_x, floatType angle_y, floatType angle_z){
        auto dir = std::any_cast<LowLevel::Vector<floatType>>(get_property("direction"));
        if (!dir.isTransposed) dir.transpose();

        LowLevel::Matrix<floatType> tait_mat = LowLevel::Matrix<floatType>::tait_bryan_matrix(angle_x,
                                                                                              angle_y,
                                                                                              angle_z);
        LowLevel::Vector<floatType> n_dir = dir * tait_mat;

        std::vector<LowLevel::Vector<floatType>> n_basis_loc_cs = local_cs.space.basis;
        for (auto & basis_vec: n_basis_loc_cs){
            basis_vec = basis_vec * tait_mat;
            if (basis_vec.isTransposed) basis_vec.transpose();
        }

        local_cs.space = LowLevel::VectorSpace<floatType>(n_basis_loc_cs);

        if (n_dir.isTransposed) n_dir.transpose();
        set_property("direction", n_dir);
    }

    LowLevel::Vector<floatType> GameObject::rotate_vec3(const LowLevel::Vector<floatType>& vec,
                                                        floatType angle_x,
                                                        floatType angle_y,
                                                        floatType angle_z){
        LowLevel::Vector<floatType> n_vec(vec);
        if (!n_vec.isTransposed) n_vec.transpose();

        LowLevel::Matrix<floatType> tait_mat = LowLevel::Matrix<floatType>::tait_bryan_matrix(angle_x,
                                                                                              angle_y,
                                                                                              angle_z);
        return n_vec * tait_mat;
    }

    // region set_methods
    void GameObject::set_position(const LowLevel::Point<floatType>& pos){
        if (pos.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("position", pos);
    }
    void GameObject::set_direction(const LowLevel::Vector<floatType>& dir){
        if (dir.size() != cs.space.dim()) throw std::exception(); // TODO: exception
        auto odir = std::any_cast<LowLevel::Vector<floatType>>(get_property("direction"));
        if (dir.size() == 3) {
            std::vector<floatType> angles = get_angles_rot(odir, dir);
            rotate_3d(angles[0], angles[1], angles[2]);
        }
        set_property("direction", dir);
    }
    // endregion

    floatType GameObject::intersection_distance(const Ray&) const{
        return 0;
    }
// endregion
} // Engine