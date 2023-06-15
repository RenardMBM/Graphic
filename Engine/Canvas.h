#ifndef GRAPHICGAME_CANVAS_H
#define GRAPHICGAME_CANVAS_H

#include "../LowLevel/LowLevel.h"
#include "GameCamera.h"
#include <SFML/Graphics.hpp>
namespace Engine {
    class Canvas {
    private:

    public:
        size_t width{};
        size_t height{};
        sf::RenderWindow window;
        LowLevel::Matrix<floatType> distances;
        LowLevel::Matrix<bool> mask;
        bool is_open{};

        Canvas();
        Canvas(const size_t&, const size_t&);
        Canvas(const Canvas&);

        Canvas& operator=(const Canvas&);

        void draw();
        void update(GameCamera&,
                    const std::vector<std::shared_ptr<Engine::GameObject>>&);

        bool close() const;
        void exit();
    };

} // BaseGame

#endif //GRAPHICGAME_CANVAS_H
