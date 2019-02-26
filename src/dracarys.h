#include "main.h"

#ifndef DRACARYS_H
#define DRACARYS_H

class Dracarys {
public:
    Dracarys() {}
    Dracarys(float x, float y, color_t color);
    glm::vec3 position;
    double velocityX;
    double velocityY;
    double gravity;
    bool onGround;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left();
    void StartJump();
    void Update();
    int come;
private:
    VAO *object;
};

#endif // BALL_H
