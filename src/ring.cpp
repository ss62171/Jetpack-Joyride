#include "ring.h"
#include "main.h"
using namespace std;

Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    int n = 500;
    double r = 2;
    //0,1,2,5,8,9,10,11
      GLfloat vertex_buffer_data[9*n];
      float theta;
      float delta = ((3.141592)) / n;
      theta = delta;
      vertex_buffer_data[0] = vertex_buffer_data[1] = vertex_buffer_data[2] = 0.0f;
      for(int i = 0; i < 9 * n; i++)
      {
          if(i % 9 == 0 || i % 9 == 1 || i % 9 == 2 || i % 9 == 5 || i % 9 == 8)
              vertex_buffer_data[i] = 0.0f;
          else if(i % 9 == 3)
              vertex_buffer_data[i] = r * cos(theta - delta);
          else if(i % 9 == 4)
              vertex_buffer_data[i] = r * sin(theta - delta);
          else if(i % 9 == 6)
              vertex_buffer_data[i] = r * cos(theta);
          else
              vertex_buffer_data[i] = r * sin(theta), theta += delta;
      }
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_YELLOW, GL_POINT);    
    }

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::move_left(){
  this->position.x -= 0.05;
}

void Ring::move_right(){
  this->position.x += 0.02;
}

