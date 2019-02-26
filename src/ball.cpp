#include "ball.h"
#include "main.h"
using namespace std;
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    //this->rotation = 0;
    this->angle = 3.141;
    this->velocityY = 0;
    this->lives = 3;
    this->is_alive = 1;
    this->velocityX = 0.0;
    this->gravity = 0.005;
    this->onGround = true;
    this->score = 0;
    this->shield_flag = 0;
    //speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
         0, 0.8,0.0, // triangle 2 : begin
         0, 0.6,0.0,
         0.2, 0.8,0.0, // triangle 2 : end

         0, 0.1, 0.0,
         0.05, 0.1, 0.0,
         0.05, 0, 0,

         0, 0.1, 0.0,
         0.0, 0.0, 0.0,
         0.05, 0.0, 0.0,

         0.17, 0.1, 0.0,
         0.22, 0.1, 0.0,
         0.22, 0.0 , 0.0,

         0.22, 0.0, 0.0,
         0.17, 0.0, 0.0,
         0.17, 0.1, 0.0,

         -0.05, 0.425, 0.0,
         0.0, 0.425, 0.0,
         0.0, 0.375, 0.0,

         0.0, 0.375, 0.0,
         -0.05, 0.375, 0.0,
         -0.05, 0.425, 0.0

          };

    static const GLfloat vertex_buffer_data1[] = {
         0, 0.6,0.0,
         0.15, 0.6, 0.0,
         0.15, 0.75, 0.0,

         0.05, 0.6, 0.0,
         0.1, 0.6, 0.0,
         0.1, 0.5, 0.0,

         0.1, 0.5, 0.0,
         0.05, 0.5, 0.0,
         0.05, 0.6, 0.0,

         0, 0.5, 0.0,
         0.17, 0.5, 0.0,
         0.17, 0.3, 0.0,

         0, 0.3, 0.0,
         0, 0.5, 0.0,
         0.17, 0.3, 0.0,
          };

    static const GLfloat vertex_buffer_data2[] = {
         0, 0.3, 0.0,
         0, 0.1, 0.0,
         0.075, 0.3, 0.0,

         0.17, 0.3, 0.0,
         0.17, 0.1, 0.0,
         0.075, 0.3, 0.0,

         -0.15, 0.5, 0.0,
         -0.05, 0.5, 0.0,
         -0.05, 0.25, 0.0,

         -0.15, 0.5, 0.0,
         -0.05, 0.25, 0.0,
         -0.15, 0.25, 0.0,
          };

    static const GLfloat vertex_buffer_data3[] = {
      -0.15, 0.2, 0.0,
      -0.1, 0.2, 0.0,
      -0.15, 0.0, 0.0,

      -0.1, 0.2, 0.0,
      -0.05, 0.2, 0.0,
      -0.05, 0.0, 0.0,

          };

    static const GLfloat vertex_buffer_data4[] = {
      -0.3, 1.2, 0.0,
      -0.3, 1.1, 0.0,
      0.34, 1.1, 0.0,

      -0.3, 1.2, 0.0,
      0.34, 1.1, 0.0,
      0.34, 1.2, 0.0,

      0.34, 1.2, 0.0,
      0.35, 1.2, 0.0,
      0.35, 0.0, 0.0,

      0.34, 1.2, 0.0,
      0.35, 0.0, 0.0,
      0.34, 0.0, 0.0,

      -0.3, 1.2, 0.0,
      -0.4, 1.2, 0.0,
      -0.3, 0.0, 0.0,

      -0.4, 1.2, 0.0,
      -0.3, 0.0, 0.0,
      -0.4, 0.0, 0.0,

    };    

    this->object = create3DObject(GL_TRIANGLES, 7*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data4, COLOR_YELLOW, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    if(!this->onGround)
    draw3DObject(this->object3);
    if(this->shield_flag == 1)
    draw3DObject(this->object4);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::StartJump()
{
        this->velocityY = 0.12;
        this->onGround = false;
}

void Ball::Update()
{
    if(this->position.x >= 3.8)
      this->position.x = 3.8;
    if(this->position.x <= -3.8)
      this->position.x = -3.8;

    if(!this->onGround)
    {
    this->velocityY -= this->gravity;
    this->position.y += this->velocityY;
    this->position.x += this->velocityX;
    }

    if(this->position.y <= -3.0f)
    {
        this->position.y = -3.0f;
        this->velocityY = 0.0;
        this->onGround = true;
        this->velocityX = 0.0;

    }

    if(this->position.y >= 3.2f)
    {
    //  this->velocityX = 0;
      this->position.y = 3.2f;
      this->velocityY *= -1;
      this->velocityY *= 0.5;
      this->velocityX = 0;

    }

}

void Ball::move_right()
{
  this->velocityX = 0.02;
  this->position.x += this->velocityX;
}


void Ball::move_left(){
  this->velocityX = -0.02;
  this->position.x += this->velocityX;

}

void Ball::move_down(){
  this->position.y -= 0.05;
}


void Ball::move_up(){
  this->position.y += 0.05;
}

int Ball::game_over(){
  if(this->is_alive == 0 && this->lives > 0)
  {
    this->position.y = -3;
    this->is_alive = 1;
    this->lives -= 1;
    cout << lives << endl;

  }
  if(this->lives <= 0)
  {
    cout << "over" << endl;
   return 0; 
  }
}

void Ball::move(float x,float y){
    this->angle -= 0.04;
    this->position.x =  x + cos(angle)*1.9;
    this->position.y =  y + sin(angle)*1.9;
}

void Ball::magnet(float x, float y){
  if(this->position.x <= x && x <= 4)
  {
    this->velocityX = 0.02;
    this->velocityY = 0.05;
    this->position.y += this->velocityY;
    this->position.x += this->velocityX;
  }

  else if(this->position.x > x && x <= 4 && x>=-4)
  {
    this->velocityX = -0.02;
    this->velocityY = 0.05;
    this->position.y += this->velocityY;
    this->position.x += this->velocityX;
  }
}