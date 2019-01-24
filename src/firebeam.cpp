#include "firebeam.h"
#include "main.h"
int down = 0 ;
doubleFirebeam::doubleFirebeam(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
           -1.0,  1.0,  0.0,
           -1.0, -1.0,  0.0,
            0.0,  1.0,  0.0, // left dumbel1
            0.0,  1.0,  0.0,
           -1.0, -1.0,  0.0,
            0.0, -1.0,  0.0, // left dumbel2
            0.0,  0.50,  0.0,
            2.0,  0.50,  0.0,
            0.0,  0.25,  0.0, //fireline1
            0.0,  0.25,  0.0,
            2.0,  0.25,  0.0,
            2.0,  0.50,  0.0, //fireline2
            0.0, -0.25,  0.0,
            2.0, -0.25,  0.0,
            0.0, -0.50,  0.0, //fireline1
            0.0, -0.50,  0.0,
            2.0, -0.50,  0.0,
            2.0, -0.25,  0.0, //fireline2
            2.0,  1.0,  0.0,
            2.0, -1.0,  0.0,
            3.0,  1.0,  0.0, // right dumbel1
            3.0,  1.0,  0.0,
            2.0, -1.0,  0.0,
            3.0, -1.0,  0.0, // right dumbel2

    };
    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
}

void doubleFirebeam::draw(glm::mat4 VP) {
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

void doubleFirebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void doubleFirebeam::tick() {
    // this->rotation += speed;
     // this->position.x -= 0.02;
     // this->position.y -= 0.001*(this->position.x)*(this->position.x);

     if ( this->position.y >= 3 ) {
       down = 1 ;
     }
     if ( this->position.y <= -1 ) {
       down = 0 ;
     }
     if (down == 1) {
       this->position.y -= 0.01;
     }
     else
     {
       this-> position.y += 0.01;
     }
}

bounding_box_t doubleFirebeam::bounding_box() {
  float x = this->position.x+0.75;
  float y = this->position.y;
  bounding_box_t doubleFirebeambox =
  {
    x, y, 2.5, 1.0,
  };
  return doubleFirebeambox;
}
