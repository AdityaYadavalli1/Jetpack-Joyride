#include "smarten.h"
#include "main.h"

Smarten::Smarten(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy = 0;
    this->lives = 2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
         -1.0f,1.0f,0.0f,
          0.0f,0.0f,0.0f,
          1.0f,1.0f,0.0f, // upper
          0.0f,0.0f,0.0f,
         -1.0f,-1.0f,0.0f,
          1.0f,-1.0f,0.0f // lower
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Smarten::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(0.5f, 0.7f ,0.5f));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Smarten::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Smarten::tick() {
    // this->rotation += speed;
    // this->position.x += this->speedx;
    // this->position.y += this->speedy;
}

bounding_box_t Smarten::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  bounding_box_t Smartenbox =
  {
    x, y, 0.5, 0.75,
  };
  return Smartenbox;
}
