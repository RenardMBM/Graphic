#ifndef GRAPHIC_ENTITIESLIST_H
#define GRAPHIC_ENTITIESLIST_H

#include <vector>
#include <memory>

#include "Entity.h"
#include "Identifier.h"
namespace Engine {

    class EntitiesList {
    private:
        std::vector<Entity> entities;
    public:
        EntitiesList();

        void append(const Entity&);
        void remove(const std::shared_ptr<Identifier>& id);
        Entity get(const std::shared_ptr<Identifier>&) const;
        void exec(std::function<void(Entity&)> func);
        size_t size() const;

        Entity& operator[](const std::shared_ptr<Identifier>&);
        Entity operator[](const std::shared_ptr<Identifier>&) const;
    };

} // Engine

#endif //GRAPHIC_ENTITIESLIST_H
