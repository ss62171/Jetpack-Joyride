#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H

class Boomerang{
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color, int origin);
    glm::vec3 position;
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
