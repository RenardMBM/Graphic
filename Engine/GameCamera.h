#ifndef GRAPHIC_GAMECAMERA_H
#define GRAPHIC_GAMECAMERA_H

#include "GameObject.h"
#include "../LowLevel/LowLevel.h"

namespace Engine {

    class GameCamera: public GameObject {
    private:
        typedef long double floatType;

        floatType calcVfov(floatType, floatType);
    public:
        GameCamera();
        GameCamera(floatType, floatType);
        GameCamera(floatType, floatType, floatType);
        GameCamera(floatType, const LowLevel::Point<floatType>&, floatType);
        GameCamera(floatType, floatType, const LowLevel::Point<floatType>&, floatType);
    };

} // Engine

#endif //GRAPHIC_GAMECAMERA_H
