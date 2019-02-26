#include "dracarys.h"
#include "main.h"
using namespace std;
Dracarys::Dracarys(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocityY = 0;
    this->velocityX = 0.0;
    this->gravity = 0.005;
    this->onGround = true;
    this->come = 0;
    //speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
         0.0, 0.8,0.0, // triangle 2 : begin
         0.8, 0.0,0.0,
         0.0, 0.0,0.0, // triangle 2 : end

          0.0, 0.8,0.0, // triangle 2 : begin
          0.8, 0.0,0.0,
          0.8, 0.8,0.0,

          };  

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Dracarys::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dracarys::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dracarys::StartJump()
{
        this->velocityY = 0.12;
        this->onGround = false;
}

void Dracarys::Update()
{
    if(!this->onGround)
    {
    this->velocityY -= this->gravity;
    this->position.y += this->velocityY;
    }

    if(this->position.y <= -3.0f)
    {
        this->position.y = -3.0f;
        this->velocityY = 0.0;
        this->onGround = true;
    }

    if(this->position.y >= 3.2f)
    {
    //  this->velocityX = 0;
      this->position.y = 3.2f;
      this->velocityY *= -1;
      this->velocityY *= 0.5;
    }

}

void Dracarys::move_left(){
  this->velocityX = -0.02;
  this->position.x += this->velocityX;

}
