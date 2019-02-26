#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coins{
public:
    Coins() {}
    Coins(float x, float y, color_t color, int score);
    glm::vec3 position;
    double velocityX;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left();
    void move_right();
    int score;


private:
    VAO *object;
};

#endif // BALL_H
