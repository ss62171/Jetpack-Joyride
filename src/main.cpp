#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "background.h"
#include "coins.h"
#include "fireline.h"
#include "firebeam.h"
#include "balloon.h"
#include "flying.h"
#include "boomerang.h"
#include "ring.h"
#include "magnet.h"
#include "segmentdisplay.h"
#include "dracarys.h"
#include<vector>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Dracarys dragon;
Segmentdisplay display,lives;
time_t curr_time,old_time;
Platform platform;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
vector<Background> background;
vector<Coins> coins;
vector<Fireline> fireline;
vector<Balloon> balloon;
vector<Flying> flying;
vector<Boomerang> boomerang;
Ring ring;
Magnet magnet;
vector<Firebeam> firebeam;
double mouse_x = 0.0, mouse_y = 0.0;
int mouse_action = 0;

Timer t60(1.0 / 60);

bounding_box_t a;
vector<bounding_box_t> b;
vector<bounding_box_t> fly,boom;


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    background[0].draw(VP);
    background[1].draw(VP);
    platform.draw(VP);
    for(std::vector<Coins>::size_type i = 0; i != coins.size(); i++)
    {
        coins[i].draw(VP);
    }

    for(std::vector<Fireline>::size_type i = 0; i != fireline.size(); i++)
    {
        fireline[i].draw(VP);
    }
    
    for(std::vector<Firebeam>::size_type i = 0; i != firebeam.size(); i++)
    {
        firebeam[i].draw(VP);
    }

    for(std::vector<Balloon>::size_type i = 0; i != balloon.size(); i++)
    {
        balloon[i].draw(VP);
    }
    for(std::vector<Flying>::size_type i = 0; i != flying.size(); i++)
    {
        flying[i].draw(VP);
    }

    for(std::vector<Boomerang>::size_type i = 0; i != boomerang.size(); i++)
    {
        boomerang[i].draw(VP);
    }

    magnet.draw(VP);
    ring.draw(VP);
    ball1.draw(VP);
    display.update(ball1.score);
    lives.update(ball1.lives);
    display.draw(VP);
    lives.draw(VP);
    dragon.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int s = glfwGetKey(window, GLFW_KEY_S);

    if (left)
    {
        ball1.move_left();
    }

    if (right)
    {
        ball1.move_right();
    }

    if (space && ball1.space_flag == 1) {
        ball1.StartJump();
        dragon.StartJump();
    }

    if(down)
    {
      ball1.move_down();

    }
    if(up)
    {
      ball1.move_up();

    }

    if(s)
    {   if(balloon.empty())
        balloon.push_back(Balloon(ball1.position.x,ball1.position.y,COLOR_RED));
    }
}

void move_all()
{
        background[0].move_left();
        background[1].move_left();
    
        for(std::vector<Coins>::size_type i = 0; i != coins.size(); i++)
        {
            coins[i].move_left();
            b[i].x = coins[i].position.x;
            b[i].y = coins[i].position.y - 0.2;

        }

        for(std::vector<Firebeam>::size_type i = 0; i != firebeam.size(); i++)
        {
            firebeam[i].move_left();

        }

        for(std::vector<Flying>::size_type i = 0; i != flying.size(); i++)
        {
            if(flying[i].position.x > 4)
            {
                flying[i].move_left();
                fly[i].x = flying[i].position.x;
                fly[i].y = flying[i].position.y;
            }
        }

        for(std::vector<Boomerang>::size_type i = 0; i != boomerang.size(); i++)
        {
            if(boomerang[i].position.x > 4)
            {
                boomerang[i].move_left();
                boom[i].x = boomerang[i].position.x;
                boom[i].y = boomerang[i].position.y;
            }
        }

        for(std::vector<Fireline>::size_type i = 0; i != fireline.size(); i++)
        fireline[i].move_left();
        
        if(dragon.come != 1)
        dragon.move_left();
        cout << dragon.position.x << endl;
        ring.move_left();
        magnet.move_left();       
        ball1.velocityX = 0;
}

void tick_elements()
{
    a.x = double(ball1.position.x);
    a.y = ball1.position.y;
    if(background[0].position.x <= -7.0 && dragon.come == 0)
    {
        background.erase(background.begin());
        background.push_back(Background(6,0.0,COLOR_YELLOW));
    }

    for(std::vector<Fireline>::size_type i = 0; i < fireline.size(); i++)
    {
        if(fireline[i].collision(ball1.position.x,ball1.position.y) && ball1.ring_flag == 1 && ball1.shield_flag == 0)
        {  
            ball1.is_alive = 0;  
            ball1.game_over();
        }

        if(fireline[i].position.x <= -7.0)
        {
            fireline[i].flag = 1;
        }
    }

    for(std::vector<Firebeam>::size_type i = 0; i < firebeam.size(); i++)
    {
        if(firebeam[i].collision(ball1.position.x,ball1.position.y) && ball1.ring_flag == 1 && ball1.shield_flag == 0)
        {  
            ball1.is_alive = 0;  
            ball1.game_over();
        }
    }

    for(std::vector<Firebeam>::size_type i = 0; i < firebeam.size(); i++)
    {
        if(firebeam[i].position.x <= -7.0)
        {
            firebeam[i].flag = 1;
        }
        firebeam[i].move_up();
    }


    for(std::vector<Fireline>::size_type i = 0; i < fireline.size(); i++)
    {
        if(!balloon.empty())
        {
            if(balloon[0].collision_fireline(fireline[i].position.x,fireline[i].position.y))
                fireline[i].flag = 1;
        }
    }

    for(std::vector<Balloon>::size_type i = 0; i < balloon.size(); i++)
    {
        balloon[i].throws();
        if(balloon[i].position.y < -3.0)
            balloon.erase(balloon.begin() + i);
    }

    for(std::vector<Flying>::size_type i = 0; i < flying.size(); i++)
    {
        if(flying[i].position.x <= 10.0)
        {
           flying[i].fly();
           fly[i].x = flying[i].position.x;
           fly[i].y = flying[i].position.y;

        }
    }

    for(std::vector<Boomerang>::size_type i = 0; i < boomerang.size(); i++)
    {
        if(boomerang[i].position.x <= 10.0)
        {
           boomerang[i].fly();
           boom[i].x = boomerang[i].position.x;
           boom[i].y = boomerang[i].position.y;

        }
    }

    // cout << ball1.position.x <<  " " << ball1.position.y << endl;
    // cout << ring.position.x <<  " " << ring.position.y << endl;
    if(((ball1.position.x - ring.position.x)*(ball1.position.x - ring.position.x) + ((ball1.position.y-ring.position.y)*(ball1.position.y-ring.position.y)) - 4 <= 0) && ball1.position.y >=0 )
    {
        ball1.move(ring.position.x, ring.position.y);
        ball1.ring_flag = 0;
    } 
    else
        ball1.ring_flag = 1;

    ball1.magnet(magnet.position.x,magnet.position.y);
    lives.set_position(-7.5,3.5);

    if(dragon.position.x <= 3)
        dragon.come = 1;
}

void erase_coin()
{
    for(std::vector<Coins>::size_type i = 0; i < coins.size(); i++)
    {
        if(detect_collision(a,b[i]))
        {
            // cout << a.height << " " << a.width << " " << a.x << " " << a.y << endl;
            // cout << "b = " << b[i].height << " " << b[i].width << " " << b[i].x << " " << b[i].y << endl;
            if(coins[i].score == 1)
                ball1.score += 10;
            else
                ball1.score += 5;
            coins.erase(coins.begin() + i );
            b.erase(b.begin() + i);
        }

        if(coins[i].position.x <= -7.0)
        {
            coins.erase(coins.begin() + i);
        }
    }

    for(std::vector<Fireline>::size_type i = 0; i < fireline.size(); i++)
    {
        if(fireline[i].flag == 1)
        fireline.erase(fireline.begin() + i);
    }    

    for(std::vector<Flying>::size_type i = 0; i < flying.size(); i++)
    {
        if(detect_collision(a,fly[i]))
        {   
            if(flying[i].color_flag == 1)
            ball1.lives += 1;
            else
            ball1.shield_flag = 1;
            flying.erase(flying.begin() + i );
            fly.erase(fly.begin() + i);
            curr_time = time(NULL);
        }
    }

     for(std::vector<Boomerang>::size_type i = 0; i < boomerang.size(); i++)
    {
        if(detect_collision(a,boom[i]) && ball1.shield_flag == 0)
        {   
            boomerang.erase(boomerang.begin() + i );
            boom.erase(boom.begin() + i);
            ball1.is_alive = 0;  
            ball1.game_over();
        }
    }
}

void make_coin()
{
    int pos[100] = {
        3, 8, 11, 17, 20, 22, 28, 30, 34, 39,
        42, 48, 51, 55, 58, 60, 64, 66, 69,
        72, 78, 80, 84, 90, 92, 96, 99, 101,
        107, 114, 119, 125, 129, 130, 134, 138,
        142, 145, 148, 154, 160, 165, 170,
        172, 176, 180, 184, 188, 191, 193, 197,
        200
    };

    for(int j=0;j<52;j++)
    {
            coins.push_back(Coins(pos[j],3.00,COLOR_BRICK,1));
            int random = j % 5;
            fireline.push_back(Fireline(pos[j]+1, j%3 - random, COLOR_BRICK));
            bounding_box_t temp;
            temp.x = pos[j]- 0.1;
            temp.y = 2.5;
            temp.width = 0.04;
            temp.height = 0.08;
            b.push_back(temp);
        j++;
        for(int i=0;i<2;i++)
        {
            coins.push_back(Coins(pos[j]+double(i)/3,0.00,COLOR_BRICK,0));
            bounding_box_t temp;
            temp.x = pos[j]+double(i)/3 - 0.1;
            temp.y = -0.5;
            temp.width = 0.04;
            temp.height = 0.08;
            b.push_back(temp);
        }
    }

    for(int j=0;j<10;j++)
    {
        firebeam.push_back(Firebeam(5+(j*12),3.00 , COLOR_BRICK,1));
        firebeam.push_back(Firebeam(5+(j*12),-3.00 , COLOR_BRICK,0));
        if(rand()%2 == 0)
        {
            flying.push_back(Flying(10+j*18,4.00,COLOR_BRICK, rand()%2,rand()%2));
            bounding_box_t temp;
            temp.x = 10+j*18;
            temp.y = 4.00;
            temp.width = 0.25;
            temp.height = 1;
            fly.push_back(temp);
        }
        else
        {
            boomerang.push_back(Boomerang(10+j*18,4.00,COLOR_BRICK, rand()%2));
            bounding_box_t temp;
            temp.x = 10+j*18;
            temp.y = 4.00;
            temp.width = 0.25;
            temp.height = 1;
            boom.push_back(temp);
        }
    }
    fireline.push_back(Fireline(0.0, 2.0, COLOR_BRICK));

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(-3, -3, COLOR_RED);
    platform = Platform(0.0,0.0,COLOR_BRICK);
    background.push_back(Background(0.0,0.0,COLOR_YELLOW));
    background.push_back(Background(6,0.0,COLOR_YELLOW));
    ring = Ring(30.0, 0.0, COLOR_BRICK);
    magnet = Magnet(37.0, 3.0, COLOR_RED);
    dragon = Dracarys(85, -3.0, COLOR_BLACK);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    make_coin();
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g /256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;
    a.width = 0.3;
    a.height = 0.15;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            erase_coin();
            if(ball1.ring_flag != 0)
                ball1.Update();
            dragon.Update();
            tick_elements();
            tick_input(window);  
            move_all();
            reset_screen();
            old_time = time(NULL);
            if(old_time - curr_time >= 5 && ball1.shield_flag == 1)
                ball1.shield_flag = 0;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        if(ball1.game_over() == 0)
            break;
    }

    quit(window);
    
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.width + b.width)) &&
           (abs(a.y - b.y)  < (a.height + b.height));
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


