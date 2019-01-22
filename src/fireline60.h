#include "main.h"

#ifndef FIRELINE60_H
#define FIRELINE60_H


class Firebeam60 {
public:
    Firebeam60() {}
    Firebeam60(float x, float y, color_t color);
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

#endif // FIRELINE60_H
