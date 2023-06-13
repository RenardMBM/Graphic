#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "Ray.h"
#include "Identifier.h"
#include "Entity.h"
#include "EntitiesList.h"
#include "Game.h"
#include "GameObject.h"
#include "GameCamera.h"

//#include "../Lowlevel/LowLevel.h"

namespace Engine {
    static size_t PRECISION = 9;

    static void set_precision(size_t precision){
        LowLevel::PRECISION = precision;
        PRECISION = precision;
    }
}

#endif //GRAPHIC_ENGINE_H
