//
// Created by renard_liss on 27.05.2023.
//
#include "Entity.h"

namespace Engine {
    Entity::Entity(const LowLevel::CoordinateSystem<floatType>& cs): cs(cs){}
    void Entity::set_property(const std::string &prop, void* value){
        if (properties.find(prop) != properties.end()) throw std::exception(); // TODO: custom exception 'existing key'
        properties[prop] = value;
    }
    void* Entity::get_property(const std::string &prop){
        if (properties.find(prop) != properties.end()) throw std::exception(); // TODO: custom exception 'non-existent key'
        return properties[prop];
    }
    void Entity::remove_property(const std::string &prop){
        if (properties.find(prop) != properties.end()) properties.erase(prop);
    }

    void* Entity::operator[](const std::string &prop){
        return get_property(prop);
    }
} // Engine