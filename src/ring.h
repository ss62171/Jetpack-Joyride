#include "main.h"

#ifndef RING_H
#define RING_H

class Ring{
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left();
    void move_right();


private:
    VAO *object;
};

#endif // BALL_H
