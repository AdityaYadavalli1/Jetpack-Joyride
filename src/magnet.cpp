#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        // -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        // -1.0f,-1.0f, 1.0f,
        // -1.0f, 1.0f, 1.0f, // triangle 1 : end
        // 1.0f, 1.0f,-1.0f, // triangle 2 : begin
        // -1.0f,-1.0f,-1.0f,
        // -1.0f, 1.0f,-1.0f, // triangle 2 : end
        // 1.0f,-1.0f, 1.0f,
        // -1.0f,-1.0f,-1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 1.0f, 1.0f,-1.0f,
        // 1.0f,-1.0f,-1.0f,
        // -1.0f,-1.0f,-1.0f,
        // -1.0f,-1.0f,-1.0f,
        // -1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f,-1.0f,
        // 1.0f,-1.0f, 1.0f,
        // -1.0f,-1.0f, 1.0f,
        // -1.0f,-1.0f,-1.0f,
        // -1.0f, 1.0f, 1.0f,
        // -1.0f,-1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 1.0f, 1.0f,-1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 1.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f,
        // 1.0f, 1.0f,-1.0f,
        // -1.0f, 1.0f,-1.0f,
        // 1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f,-1.0f,
        // -1.0f, 1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f,
        // -1.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f
        0.0, 0.0, 0.0,
        0.5, 0.0, 0.0,
        0, 1, 0,
        0, 1, 0,
        0.5, 1, 0,
        0.5, 0, 0,
        0.5, 1, 0,
        0.5, 0.8, 0,
        1, 0.8, 0,
        1, 0.8, 0,
        1, 1, 0,
        0.5, 1, 0,
        1, 1, 0,
        1, 0, 0,
        1.5, 0, 0,
        1.5, 0, 0,
        1.5, 1, 0,
        1, 1, 0,

    };

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Magnet::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  bounding_box_t magnetbox =
  {
    x, y, 1, 0.5,
  };
  return magnetbox;
}