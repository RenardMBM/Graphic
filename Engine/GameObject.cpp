#include "GameObject.h"

namespace Engine {
// region constructors
    GameObject::GameObject(const LowLevel::CoordinateSystem<floatType>& cs): Entity(cs){
        set_property("isFixedLook", false);
        set_position(LowLevel::Point<floatType>(cs.space.dim()));
        set_direction(LowLevel::Vector<floatType>(cs.space.dim(), 1l));
    }
    GameObject::GameObject(const LowLevel::Point<floatType> &pos,
                           const LowLevel::Vector<floatType>& dir,
                           const LowLevel::CoordinateSystem<floatType>& cs): Entity(cs){
        if (pos.size() != dir.size() || pos.size() != cs.space.dim()) throw std::exception(); // TODO: exception

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

        LowLevel::Vector<floatType> n_dir = dir * LowLevel::Matrix<floatType>::rotation_matrix(inds,
                                                                                               angle,
                                                                                               dir.size());
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
        if (n_dir.isTransposed) n_dir.transpose();
        set_direction(n_dir);
    }

    // region set_methods
    void GameObject::set_position(const LowLevel::Point<floatType>& pos){
        if (pos.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("position", pos);
    }
    void GameObject::set_direction(const LowLevel::Vector<floatType>& dir){
        if (dir.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("direction", dir);
    }
    // endregion
// endregion
} // Engine