#ifndef GRAPHICGAME_CANVAS_H
#define GRAPHICGAME_CANVAS_H

#include "../LowLevel/LowLevel.h"
#include "GameCamera.h"
#include <SFML/Graphics.hpp>
namespace Engine {
    class Canvas {
    private:
        sf::RenderWindow window;
        size_t m;
        size_t n;
        LowLevel::Matrix<floatType> distances;
        LowLevel::Matrix<bool> mask;
        bool is_open;
    public:
        Canvas();
        Canvas(const size_t&, const size_t&);

        void draw();
        void update(GameCamera&,
                    const std::vector<std::shared_ptr<Engine::GameObject>>&);

        bool close() const;
        void exit();
    };

} // BaseGame

#endif //GRAPHICGAME_CANVAS_H
