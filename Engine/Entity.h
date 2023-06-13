#ifndef GRAPHIC_ENTITY_H
#define GRAPHIC_ENTITY_H

#include <string>
#include <map>
#include <memory>
#include <any>

#include "../LowLevel/LowLevel.h"
#include "Identifier.h"

namespace Engine {
    typedef long double floatType;

    class Entity {
    public:
        LowLevel::CoordinateSystem<floatType> cs;
        std::shared_ptr<Identifier> identifier;
        std::map<std::string, std::any> properties;

        explicit Entity();
        explicit Entity(const LowLevel::CoordinateSystem<floatType>&);
        Entity(const Entity&);

        void set_property(const std::string&, const std::any&);
        std::any get_property(const std::string&) const;
        void remove_property(const std::string&);

        std::any operator[](const std::string&) const;
        std::any& operator[](const std::string&);
    };

} // Engine

#endif //GRAPHIC_ENTITY_H
