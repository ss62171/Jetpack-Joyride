#include "platform.h"
#include "main.h"
using namespace std;
Platform::Platform(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
        static const GLfloat vertex_buffer_data[] = {
        -4.0f,-4.0f,0.0f, // triangle 1 : begin
        4.0f,-4.0f, 0.0f,
        -4.0f, -3.0f, 0.0f, // triangle 1 : end
        -4.0f, -3.0f, 0.0f, // triangle 2 : begin
        4.0f,-3.0f,0.0f,
        4.0f, -4.0f,0.0f, // triangle 2 : end
          };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Platform::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
