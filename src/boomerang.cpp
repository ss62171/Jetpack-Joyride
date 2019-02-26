#include "boomerang.h"
#include "main.h"
using namespace std;

Boomerang::Boomerang(float x, float y, color_t color, int origin) {
    this->position = glm::vec3(x, y, 0);
    this->velocityX = 0.04;
    this->velocityY = 0.2;
    this->origin = origin;

    
    GLfloat vertex_buffer_data[] = {
        0.0, 0.0, 0.0,
        0.4, 0.4, 0.0,
        0.2, 0.0, 0.0,

        0.0, 0.0, 0.0,
        0.2, 0.0, 0.0,
        0.4, -0.4, 0.0
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::fly()
{   if(this->origin ==0)
        this->position.y -= 0.05;
    else
        this->position.y -= 0.05*this->origin;
    this->position.x = ((this->position.y * this->position.y)/4) - this->origin;
}

void Boomerang::move_left(){
  this->position.x -= 0.05;
}
