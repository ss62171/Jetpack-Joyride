#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H

class Fireline{
public:
    Fireline() {}
    Fireline(float x, float y, color_t color);
    glm::vec3 position;
    double velocityX;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left();
    void move_right();
    int flag;
    bool linesTouching(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    bool collision(float x3, float y3);
    

private:
    VAO *object;
};

#endif // BALL_H
