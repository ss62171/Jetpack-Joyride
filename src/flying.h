#include "main.h"

#ifndef FLYING_H
#define FLYING_H

class Flying{
public:
    Flying() {}
    Flying(float x, float y, color_t color, int origin, int color_flag);
    glm::vec3 position;
    int color_flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float velocityX;
    float velocityY;
    int origin;
    void fly();
    void move_left();

private:
    VAO *object;
};

#endif // BALL_H
