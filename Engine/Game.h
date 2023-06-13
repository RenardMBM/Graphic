#ifndef GRAPHIC_GAME_H
#define GRAPHIC_GAME_H

#include "Entity.h"
#include "Ray.h"
#include "EntitiesList.h"
#include "EntitiesList.h"
#include "../LowLevel/LowLevel.h"

namespace Engine {
    class Game{
    private:
        LowLevel::CoordinateSystem<floatType> cs;
        EntitiesList entities;
    public:
        Game();
        Game(const LowLevel::CoordinateSystem<floatType>&, const EntitiesList&);

        void run();
        void update();
        void exit();

        Entity get_entity_class();
        Ray get_ray_class(const LowLevel::Point<floatType>&, const LowLevel::Vector<floatType>&);
    };

}  // Engine

#endif //GRAPHIC_GAME_H
