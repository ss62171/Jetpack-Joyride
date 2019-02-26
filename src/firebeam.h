#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H

class Firebeam{
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color, int direction);
    glm::vec3 position;
    int direction;
    double velocityX;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left();
    void move_right();
    void move_up();
    bool linesTouching(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    bool collision(float x3, float y3);
    int flag;
    

private:
    VAO *object;
};

#endif // BALL_H
