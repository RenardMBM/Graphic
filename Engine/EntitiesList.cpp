#include "EntitiesList.h"

namespace Engine {
    EntitiesList::EntitiesList() = default;

    Entity& EntitiesList::operator[](const std::shared_ptr<Identifier>& id){
        for (Entity& e: entities){
            if (e.identifier->get_value() == id->get_value()) {
                return e;
            }
        }
        throw std::range_error("non-existent key: " + id->get_value());
    }
    Entity EntitiesList::operator[](const std::shared_ptr<Identifier>& id) const{
        for (const Entity& e: entities){
            if (e.identifier->get_value() == id->get_value()) {
                return e;
            }
        }
        throw std::range_error("non-existent key: " + id->get_value());
    }

    Entity EntitiesList::get(const std::shared_ptr<Identifier>& id) const{
        return operator[](id);
    }
    void EntitiesList::append(const Entity& entity){
        entities.push_back(entity);
    }
    void EntitiesList::remove(const std::shared_ptr<Identifier>& id){
        for (auto it = entities.begin(); it != entities.end(); ++it){
            if ((*it).identifier->get_value() == id->get_value()) {
                entities.erase(it);
                break;
            }
        }
    }
    void EntitiesList::exec(std::function<void(Entity&)> func) {
        for (Entity &e: entities) {
            func(e);
        }
    }
    size_t EntitiesList::size() const{
        return entities.size();
    }
} // Engine