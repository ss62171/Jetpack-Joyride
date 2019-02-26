#include "background.h"
#include "main.h"
using namespace std;
Background::Background(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocityX = 0.0;
    this->ratio = 7.5;
    // this->a = -9.8;
    // this->b = -7.3;
    // this->c = -6;
    // this->d = -4.5;
        static const GLfloat vertex_buffer_data[] = {
          -2.3, 2.3, 0.0,
          0.2, 2.3, 0.0,
          0.2, -1.6, 0.0,

          0.2, -1.6, 0.0,
          -2.3, -1.6, 0.0,
          -2.3, 2.3, 0.0,

          1.5, 2.3, 0.0,
          3, 2.3, 0.0,
          3, -1.6, 0.0,

          3, -1.6, 0.0,
          1.5, -1.6, 0.0,
          1.5, 2.3, 0.0,
          };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
}

void Background::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Background::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Background::move_right()
{
  this->velocityX = 0.05;
  this->position.x += this->velocityX;
}


void Background::move_left(){
  this->velocityX = -0.05;
  this->position.x += this->velocityX;

}
