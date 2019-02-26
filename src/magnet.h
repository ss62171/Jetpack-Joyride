#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet{
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left();

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // BALL_H
