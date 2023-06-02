#include "Game.h"

namespace Engine {
    Game::Game(): Entity() {}
    Game::Game(const LowLevel::CoordinateSystem<floatType>& cs, const EntitiesList& el): Entity(cs),
                                                                                         entities(el){}

    Entity Game::get_entity_class() {
        return Entity(cs);
    }

    Ray Game::get_ray_class(const LowLevel::Point<floatType>& init_pt, const LowLevel::Vector<floatType>& direction) {
        return Ray(cs, init_pt, direction);
    }
} // Engine
