#include "coins.h"
#include "main.h"

Coins::Coins(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 1;
    int n = 50;
    GLfloat vertex_buffer_data[3*3*n];
    float pi = 22 * 1.0f / 7;
    float delta = 2 * pi / n;
    float theta = 0;
    for(int i = 0;i < n;i++){
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i+1] = 0.0f;
        vertex_buffer_data[9*i+2] = 0.0f;

        vertex_buffer_data[9*i+3] = 0.5 * cos(theta);
        vertex_buffer_data[9*i+4] = 0.5 * sin(theta);
        vertex_buffer_data[9*i+5] = 0.0f;

        theta += delta;
        vertex_buffer_data[9*i+6] = 0.5 * cos(theta);
        vertex_buffer_data[9*i+7] = 0.5 * sin(theta);
        vertex_buffer_data[9*i+8] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 50*3, vertex_buffer_data, color, GL_FILL);
}

void Coins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(0.3f, 0.3f ,0.3f));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coins::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
bounding_box_t Coins::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  bounding_box_t coinbox =
  {
    x, y, 0.2, 0.2,
  };
  return coinbox;
}
