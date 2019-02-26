#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H

class Balloon{
public:
    Balloon() {}
    Balloon(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float velocityX;
    float velocityY;
    float gravity;
    void throws();
    float distance(float x1, float y1, float x2, float y2);
    bool collision_fireline(float x, float y);

private:
    VAO *object;
};

#endif // BALL_H
