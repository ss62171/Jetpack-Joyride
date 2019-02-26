#include "main.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background {
public:
    Background() {}
    Background(float x, float y, color_t color);
    glm::vec3 position;
    double velocityX;
    double ratio;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_left();
    void move_right();

private:
    VAO *object;
};

#endif // BALL_H
