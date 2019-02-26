#include "coins.h"
#include "main.h"
using namespace std;
Coins::Coins(float x, float y, color_t color, int score) {
    this->position = glm::vec3(x, y, 0);
    this->velocityX = 0.0;
    int n = 500;
    int i;
    this->score = score;
    double r = 0.1;
    double theta = 0;
    double delta = (2*3.141)/n;
    //0,1,2,5,8,9,10,11
    GLfloat vertex_buffer_data[9*n];
    vertex_buffer_data[3] = r;
    vertex_buffer_data[4] = 0.0;

    for(i=0;i<9*n;i++)
    {
        if(i%9 == 8)
        {
            theta = delta;
            delta += delta;
        }
        if(i%9 == 0 || i%9 == 1 || i%9 == 2 || i%9 == 5 || i%9 == 8) 
            vertex_buffer_data[i] = 0.0;
        

        else if(i%9 == 3)
        {
            vertex_buffer_data[i] = r*cos(theta);
            vertex_buffer_data[i+1] = r*sin(theta);
        }

        else if(i%9 == 6)
        {
            vertex_buffer_data[i] = r*cos(theta + delta);
            vertex_buffer_data[i+1] = r*sin(theta + delta);
        }

    }

    if(score == 1)
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    else
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);

}

void Coins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coins::move_right()
{
  this->velocityX = 0.05;
  this->position.x += this->velocityX;
}


void Coins::move_left(){
  this->velocityX = -0.05;
  this->position.x += this->velocityX;
}

