#ifndef GRAPHICGAME_CANVAS_H
#define GRAPHICGAME_CANVAS_H

#include "../LowLevel/LowLevel.h"
#include "GameCamera.h"
namespace Engine {

    class Canvas {
    private:
        size_t m;
        size_t n;
        LowLevel::Matrix<floatType> distances;
        LowLevel::Matrix<bool> mask;
    public:
        Canvas(const size_t&, const size_t&);

        void draw();
        void update(GameCamera&,
                    const std::vector<std::shared_ptr<Engine::GameObject>>&) const;
    };

} // BaseGame

#endif //GRAPHICGAME_CANVAS_H
