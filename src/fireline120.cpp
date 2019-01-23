#include "fireline120.h"
#include "main.h"

Firebeam120::Firebeam120(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat middle_buffer_data[] = {
        // -1.0, 2.0, 0.0,
        //  0.0, 3.0, 0.0,
        //  1.0, 2.0, 0.0, // left dumbel1
        //  1.0, 2.0, 0.0,
        // -1.0, 2.0, 0.0,
        //  0.0, 1.0, 0.0, // left dumbel2
        0.56,2.75, 0.0,
        2.56,0.75, 0.0,
        0.19,2.25, 0.0, // fireline1
        2.56,0.75, 0.0,
        0.19,2.25, 0.0,
        2.19,0.25, 0.0, // fireline2
        // 2.0, 1.0, 0.0,
        // 1.0, 0.0, 0.0,
        // 3.0, 0.0, 0.0, // right dumbel1
        // 3.0, 0.0, 0.0,
        // 1.0, 0.0, 0.0,
        // 2.0,-1.0, 0.0, // right dumbel2

    };
    int n = 50;
    GLfloat left_buffer_data[3*3*n];
    float pi = 22 * 1.0f / 7;
    float delta = 2 * pi / n;
    float theta = 0;
    for(int i = 0;i < n;i++){
        left_buffer_data[9*i] = 0.15f;
        left_buffer_data[9*i+1] = 2.75f;
        left_buffer_data[9*i+2] = 0.6f;

        left_buffer_data[9*i+3] = 0.5 * cos(theta) + 0.15f;
        left_buffer_data[9*i+4] = 0.5 * sin(theta) + 2.75f;
        left_buffer_data[9*i+5] = 0.4f;

        theta += delta;
        left_buffer_data[9*i+6] = 0.5 * cos(theta) + 0.15f;
        left_buffer_data[9*i+7] = 0.5 * sin(theta) + 2.75f;
        left_buffer_data[9*i+8] = 0.6f;
    }
    GLfloat right_buffer_data[3*3*n];
    theta = 0;
    for(int i = 0;i < n;i++){
        right_buffer_data[9*i] = 2.45f;
        right_buffer_data[9*i+1] = 0.35f;
        right_buffer_data[9*i+2] = 0.6f;

        right_buffer_data[9*i+3] = 0.5 * cos(theta) + 2.45f;
        right_buffer_data[9*i+4] = 0.5 * sin(theta) + 0.35f;
        right_buffer_data[9*i+5] = 0.4f;

        theta += delta;
        right_buffer_data[9*i+6] = 0.5 * cos(theta) + 2.45f;
        right_buffer_data[9*i+7] = 0.5 * sin(theta) + 0.35f;
        right_buffer_data[9*i+8] = 0.6f;
    }
    GLfloat vertex_buffer_data[18 + 450 + 450];
    for (int i = 0; i < 18; i++) {
      vertex_buffer_data[i] = middle_buffer_data[i];
    }
    for ( int i = 0; i < 450; i++) {
      vertex_buffer_data[i+18] = left_buffer_data[i];
    }
    for ( int i = 0; i < 450; i++) {
      vertex_buffer_data[i+18+450] = right_buffer_data[i];
    }
    this->object = create3DObject(GL_TRIANGLES, 102*3, vertex_buffer_data, color, GL_FILL);
}

void Firebeam120::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 scale = glm::scale(glm::vec3(0.8f, 0.8f ,0.8f));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam120::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam120::tick() {
    // this->rotation += speed;
     // this->position.x -= 0.02;
     // this->position.y -= 0.001*(this->position.x)*(this->position.x);
}

bounding_box_t Firebeam120::bounding_box() {
  float x = this->position.x + 1.75;
  float y = this->position.y + 1.50;
  bounding_box_t Firebeambox120 =
  {
    x, y, 2.25, 1.75,
  };
  return Firebeambox120;
}
