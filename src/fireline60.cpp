#include "fireline60.h"
#include "main.h"

Firebeam60::Firebeam60(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
           -1.0,  0.0,  0.0,
          -0.25, -1.0,  0.0,
            0.0,  1.0,  0.0, // left dumbel1
            0.0,  1.0,  0.0,
           0.75,  0.0,  0.0,
          -0.25, -1.0,  0.0, // left dumbel2
           0.19, 0.75,  0.0,
           0.56, 0.25,  0.0,
           2.19, 2.75,  0.0, // fireline1
           0.56, 0.25,  0.0,
           2.19, 2.75,  0.0,
           2.56, 2.25,  0.0, // fireline2
            1.0,  2.0,  0.0,
           1.75,  1.0,  0.0,
            2.0,  3.0,  0.0, // right dumbel1
           1.75,  1.0,  0.0,
            2.0,  3.0,  0.0,
           2.75,  2.0,  0.0, // right dumbel2

    };

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Firebeam60::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(0.5f, 0.5f ,0.5f));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam60::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam60::tick() {
    // this->rotation += speed;
     // this->position.x -= 0.02;
     // this->position.y -= 0.001*(this->position.x)*(this->position.x);
}

bounding_box_t Firebeam60::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  bounding_box_t Firebeambox60 =
  {
    x, y, 0.45, 1.5,
  };
  return Firebeambox60;
}
