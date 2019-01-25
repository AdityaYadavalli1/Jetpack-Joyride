#include "main.h"

#ifndef SMARTEN_H
#define SMARTEN_H


class Smarten {
public:
    Smarten() {}
    Smarten(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float speedx;
    float speedy;
    int lives;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    // double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SMARTEN_H
