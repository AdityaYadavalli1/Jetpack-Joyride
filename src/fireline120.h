#include "main.h"

#ifndef FIRELINE120_H
#define FIRELINE120_H


class Firebeam120 {
public:
    Firebeam120() {}
    Firebeam120(float x, float y, color_t color);
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

#endif // FIRELINE120_H
