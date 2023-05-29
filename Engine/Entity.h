#ifndef GRAPHIC_ENTITY_H
#define GRAPHIC_ENTITY_H

#include <string>
#include <map>
#include <memory>

#include "../LowLevel/LowLevel.h"
#include "Identifier.h"

namespace Engine {
    class Entity {
    private:
        typedef long double floatType;
    public:
        LowLevel::CoordinateSystem<floatType> cs;
        std::unique_ptr<Identifier> identifier;
        std::map<std::string, void*> properties;

        explicit Entity(const LowLevel::CoordinateSystem<floatType>&);

        void set_property(const std::string&, void*);
        void* get_property(const std::string&);
        void remove_property(const std::string&);

        void* operator[](const std::string&);
    };

} // Engine

#endif //GRAPHIC_ENTITY_H
