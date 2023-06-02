#include "Entity.h"

namespace Engine {
    Entity::Entity(): cs(
            LowLevel::CoordinateSystem<floatType>(
                    LowLevel::Point<floatType>(3, 0),
                            LowLevel::VectorSpace<floatType>({
                                LowLevel::Vector<floatType>({1, 0, 0}),
                                LowLevel::Vector<floatType>({0, 1, 0}),
                                LowLevel::Vector<floatType>({0, 0, 1})}))
            ){}
    Entity::Entity(const LowLevel::CoordinateSystem<floatType>& cs): cs(cs){}
    Entity::Entity(const Entity& entity) = default;

    void Entity::set_property(const std::string& prop, const std::any& value){
        properties[prop] = value;
    }
    std::any Entity::get_property(const std::string &prop) const{
        auto it = properties.find(prop);
        if (it == properties.end()) throw std::range_error("non-existent key: " + prop);
        return it->second;
    }
    void Entity::remove_property(const std::string &prop){
        if (properties.find(prop) != properties.end()) properties.erase(prop);
    }

    std::any Entity::operator[](const std::string& prop) const{
        return get_property(prop);
    }

    std::any& Entity::operator[](const std::string &prop){
        auto it = properties.find(prop);
        if (it == properties.end()) throw std::range_error("non-existent key: " + prop);
        return it->second;;
    }
} // Engine