#include "GameObject.h"

namespace Engine {

    GameObject::GameObject(){
        set_property("position", LowLevel::Point<floatType>(cs.space.dim()));
        set_property("direction", LowLevel::Vector<floatType>(cs.space.dim()));
    }
    GameObject::GameObject(const LowLevel::Point<floatType> &pos, const LowLevel::Vector<floatType>& dir){
        if (pos.size() != dir.size() || pos.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("position", pos);
        set_property("direction", dir);
    }

    void GameObject::move(const LowLevel::Vector<floatType>& vec){
        if (vec.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("position", std::any_cast<LowLevel::Point<floatType>>(get_property("position")) + vec);
    }
    void GameObject::planar_rotate(const std::pair<size_t, size_t>& inds, floatType angle){
        // TODO: check params
        auto dir = std::any_cast<LowLevel::Vector<floatType>>(get_property("direction"));
        bool flagT = dir.isTransposed;
        if (!flagT) dir.transpose();

        set_property("direction", dir * LowLevel::Matrix<floatType>::rotation_matrix(inds, angle, dir.size()));
    }
    void GameObject::rotate_3d(floatType angle_x, floatType angle_y, floatType angle_z){
        auto dir = std::any_cast<LowLevel::Vector<floatType>>(get_property("direction"));
        bool flagT = dir.isTransposed;
        if (!flagT) dir.transpose();

        set_property("direction",
                     dir * LowLevel::Matrix<floatType>::tait_bryan_matrix(angle_x,
                                                                          angle_y,
                                                                          angle_z));
    }
    void GameObject::set_position(const LowLevel::Point<floatType>& pos){
        if (pos.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("position", pos);
    }
    void GameObject::set_direction(const LowLevel::Vector<floatType>& dir){
        if (dir.size() != cs.space.dim()) throw std::exception(); // TODO: exception

        set_property("direction", dir);
    }
} // Engine