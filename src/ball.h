#include "main.h"

#ifndef BALL_H
#define BALL_H

class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    int score;
    double angle = 0,result;
    int ring_flag,temp_flag;
    int is_alive;
    int lives;
    float rotation;
    double velocityX;
    double velocityY;
    double gravity;
    bool onGround;
    int space_flag = 1,shield_flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_right();
    void move_left();
    void move_down();
    void move_up();
    int game_over();
    void StartJump();
    void Update();
    void move(float x,float y);
    void magnet(float x,float y);

    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;



};

#endif // BALL_H
