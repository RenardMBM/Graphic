#include "Game.h"

namespace Engine {
    Game::Game() = default;
    Game::Game(const LowLevel::CoordinateSystem<floatType>& cs, const EntitiesList& el): cs(cs),
                                                                                         entities(el){}

    Entity Game::get_entity_class() {
        return Entity(cs);
    }

    void Game::run(){};
    void Game::update(){};
    void Game::exit(){};

    Ray Game::get_ray_class(const LowLevel::Point<floatType>& init_pt, const LowLevel::Vector<floatType>& direction) {
        return {cs, init_pt, direction};
    }
} // Engine
