#include "main.h"

#ifndef HUMP_H
#define HUMP_H


class Hump {
public:
    Hump() {}
    Hump(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    // float speedx;
    // float speedy;
    // int score;
    // int lives;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    // double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // HUMP_H
