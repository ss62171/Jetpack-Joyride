#include "balloon.h"
#include "main.h"
using namespace std;

Balloon::Balloon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocityX = 0.04;
    this->velocityY = 0.2;
    this->gravity = 0.005;
    int n = 500;
    int i;
    double r = 0.15;
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

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balloon::throws()
{
    this->position.x += this->velocityX;
    if(this->position.y >= -3.0)
    {
        this->velocityY -= this->gravity;
        this->position.y += this->velocityY;
    }
}

float Balloon::distance(float x1, float y1, float x2, float y2) 
{ 
    // Calculating distance 
    return sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) * 1.0); 
} 

bool Balloon::collision_fireline(float x, float y)
{
    float lineLen = distance(x,y,x+1,y+1);
    float d1 = distance(x,y, this->position.x,this->position.y);
    float d2 = distance(x+1,y+1, this->position.x,this->position.y);
    float buffer = 0.1;

    if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer)
    {
        return true;
    }
    return false;
}

