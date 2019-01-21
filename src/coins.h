#include "main.h"

#ifndef COINS_H
#define COINS_H


class Coins {
public:
    Coins() {}
    Coins(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Coins_H
