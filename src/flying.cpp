#include "flying.h"
#include "main.h"
using namespace std;

Flying::Flying(float x, float y, color_t color, int origin, int color_flag) {
    this->position = glm::vec3(x, y, 0);
    this->velocityX = 0.04;
    this->velocityY = 0.2;
    this->origin = origin;
    this->color_flag = color_flag;

    
    GLfloat vertex_buffer_data[] = {
        0.0, 0.0, 0.0,
        0.4, 0.4, 0.0,
        0.2, 0.0, 0.0,

        0.0, 0.0, 0.0,
        0.2, 0.0, 0.0,
        0.4, -0.4, 0.0
    };
    if(this->color_flag == 1)
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    else
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);

}

void Flying::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Flying::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Flying::fly()
{   if(this->origin ==0)
        this->position.y -= 0.05;
    else
        this->position.y -= 0.05*this->origin;
    this->position.x = ((this->position.y * this->position.y)/4) - this->origin;
}

void Flying::move_left(){
  this->position.x -= 0.05;
}
