#include "firebeam.h"
#include "main.h"
using namespace std;
    int up_flag = 0;
    int down_flag = 0;
Firebeam::Firebeam(float x, float y, color_t color, int direction) {
    this->position = glm::vec3(x, y, 0);
    this->velocityX = 0.0;
    this->flag = 0;

    this->direction = direction;
    GLfloat vertex_buffer_data[] = {
        0.0, 0.0, 0.0,
        0.2, 0.0, 0.0,
        0.0, 0.2, 0.0,

        0.0, 0.2, 0.0,
        0.2, 0.2, 0.0,
        0.2, 0.0, 0.0,

        0.2, 0.06, 0.0,
        0.2, 0.12, 0.0,
        2, 0.06, 0.0,

        0.2, 0.12, 0.0,
        2, 0.06, 0.0,
        2, 0.12, 0.0,

        2.0, 0.0, 0.0,
        2, 0.2, 0.0,
        2.2, 0.0, 0.0,

        2, 0.2, 0.0,
        2.2, 0.0, 0.0,
        2.2, 0.2, 0.0
        };

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_BRICK, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::move_right()
{
  this->velocityX = 0.05;
  this->position.x += this->velocityX;
}


void Firebeam::move_left(){
  this->velocityX = -0.05;
  this->position.x += this->velocityX;
}

void Firebeam::move_up(){
    if(this->direction == 0 && down_flag == 0)
        this->position.y += 0.01;
    
    if(this->direction == 0 && down_flag == 1)
        this->position.y -= 0.01;

    if(this->direction == 0 && this->position.y >= -0.08)
        down_flag = 1;
    
    if(this->direction == 0 && this->position.y <= -3)
        down_flag = 0;


    if(this->direction == 1 && up_flag == 0)
        this->position.y -= 0.01;
    
    if(this->direction == 1 && up_flag == 1)
        this->position.y += 0.01;

    if(this->direction == 1 && this->position.y <= 0.08)
        up_flag = 1;
    
    if(this->direction == 1 && this->position.y >= 3)
        up_flag = 0;
}

bool Firebeam::linesTouching(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
  float denominator = ((x2 - x1) * (y4 - y3)) - ((y2 - y1) * (x4 - x3));
  float numerator1 = ((y1 - y3) * (x4 - x3)) - ((x1 - x3) * (y4 - y3));
  float numerator2 = ((y1 - y3) * (x2 - x1)) - ((x1 - x3) * (y2 - y1));

  // Detect coincident lines (has a problem, read below)
  if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

  float r = numerator1 / denominator;
  float s = numerator2 / denominator;
  return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool Firebeam::collision(float x3, float y3)
{   
    bool left = linesTouching(x3-0.15,y3,x3-0.15,y3+0.8,this->position.x,this->position.y,this->position.x+2,this->position.y+0.2);
    bool right = linesTouching(x3+0.17,y3,x3+0.17,y3+0.8,this->position.x,this->position.y,this->position.x+2,this->position.y+0.2);
    bool top = linesTouching(x3-0.15,y3+0.8,x3+0.17,y3+0.8,this->position.x,this->position.y,this->position.x+2,this->position.y+0.2);
    bool bottom = linesTouching(x3-0.15,y3,x3+0.17,y3,this->position.x,this->position.y,this->position.x+2,this->position.y+0.2);

    if(left || right || top || bottom)
        return true;
    

}