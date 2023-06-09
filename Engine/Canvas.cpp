#include "Canvas.h"

namespace Engine {
    Canvas::Canvas() = default;
    Canvas::Canvas(const size_t& height, const size_t& width): height(height),
                                                               width(width),
                                                      distances(height, width, -1),
                                                      mask(height, width, false),
                                                      window(sf::RenderWindow(
                                                              sf::VideoMode(width,
                                                                                 height),
                                                                "Game")),
                                                      is_open(true){}
    Canvas::Canvas(const Canvas& other): height(other.height),
                                         width(other.width),
                                         distances(other.distances),
                                         mask(other.mask),
                                         is_open(other.is_open){
        window.create(sf::VideoMode(width,
                                    height),
                      "Game");
    }
    Canvas& Canvas::operator=(const Canvas& other){
        height = other.height;
        width = other.width;
        distances = other.distances;
        mask = other.mask;
        is_open = other.is_open;
        window.create(sf::VideoMode(width,
                                    height),
                      "Game");
        return *this;
    }
    void Canvas::draw(){
        auto *pixels  = new sf::Uint8[width * height * 4];

        sf::Texture texture;
        texture.create(width, height);

        sf::Sprite sprite(texture);

        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                size_t k = i * j * 4;
                if (mask[i][j]) {
                    pixels[k] = 255;
                    pixels[k + 1] = 255;
                    pixels[k + 2] = 255;
                    pixels[k + 3] = 1;
                }
                else{
                    pixels[k] = 0;
                    pixels[k + 1] = 0;
                    pixels[k + 2] = 0;
                    pixels[k + 3] = 1;
                }
            }
        }
        texture.update(pixels);
        //window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    void Canvas::update(GameCamera& camera,
                        const std::vector<std::shared_ptr<GameObject>>& objs){
        LowLevel::Matrix<Ray> rays_mat = camera.get_rays_matrix(height, width);

        for (size_t i = 0; i < height; ++i){
            for (size_t j = 0; j < width; ++j){
                if (mask[i][j]) continue;

                Ray ray = rays_mat[i][j];
                for (const auto& obj: objs){
                    floatType dist = obj->intersection_distance(ray);
                    if (distances[i][j] < 0 || dist < distances[i][j]) {
                        distances[i][j] = dist;
                        if (dist < camera.get_drawDistance() * ray.direction.length()){
                            mask[i][j] = true;
                        }
                    }
                }
            }
        }
//        sf::RenderWindow().pollEvent()
        if (window.isOpen()){
            sf::Event event{};
            while(window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    is_open = false;
            }
        }
    }

    bool Canvas::close() const{
        return !is_open;
    }

    void Canvas::exit(){
        window.close();
    }
} // BaseGame