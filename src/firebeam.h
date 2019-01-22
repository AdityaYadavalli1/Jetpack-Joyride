#include "main.h"

#ifndef DOUBLEFIREBEAMS_H
#define DOUBLEFIREBEAMS_H


class doubleFirebeam {
public:
    doubleFirebeam() {}
    doubleFirebeam(float x, float y, color_t color);
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

#endif // DOUBLEFIREBEAMS_H
