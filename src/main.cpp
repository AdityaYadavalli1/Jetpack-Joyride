#include "main.h"
#include "timer.h"
#include "ball.h"
#include "coins.h"
#include "magnet.h"
#include "sfo.h"
#include "firebeams.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Coins coins[4];
Coins doublecoins[4];
Magnet magnet;
Sfo Sfo1;
Firebeam Firebeam1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float pointx = 0;
float pointy = 2;
float zoom = 1;
int tickcounter = 0;
int magnetdisappear = 0;
// int ycordcoin = rand() % 7 - 3; // -3 to 3
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
int createrandforcoin() {
  return ( rand() % 4  );
}
int createrandformagnet() {
  return ( rand() % 3 + 1);
}
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (pointx, 0, zoom);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (pointx, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    for (int i=0; i<4; i++)
    {
      coins[i].draw(VP);
    }
    for (int i=0; i<4; i++)
    {
      doublecoins[i].draw(VP);
    }
    magnet.draw(VP);
    magnetdisappear = createrandformagnet();
    // coin.draw(VP);
    // ball2.draw(VP);
    Sfo1.draw(VP);
    Firebeam1.draw(VP);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs((a.x) - (b.x)) * 1 < (a.width + b.width)) &&
           (abs((a.y) - (b.y)) * 1 < (a.height + b.height));
}
bool under_magnet_influence(bounding_box_t player, bounding_box_t magnet) {
    return (abs((player.x) - (magnet.x)) < (player.width  + magnet.width)*3) &&
           (abs((player.y) - (magnet.y)) < (player.height + magnet.height)*3);
}
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int top   = glfwGetKey(window, GLFW_KEY_UP);
    int bottom= glfwGetKey(window, GLFW_KEY_DOWN);
    if (left) {
        // Do something
        ball1.position.x -= 0.02;
        pointx -= 0.02;
    }
    if (right) {

      ball1.position.x += 0.02;// change the ball's position so that it stays still but the rest is moving
      pointx += 0.02;//change the point you are looking
    }
    if (top) {
      if (ball1.position.y < 2)
      {
          ball1.position.y += 0.04;
      }
    }
    else if (!under_magnet_influence(ball1.bounding_box(),magnet.bounding_box()))
    {
      if (ball1.position.y >= -2.5)
      {
          ball1.position.y -= 0.04;
      }
    }
}


void tick_elements() {
    ball1.tick();
    magnet.tick();
    bool Sfo1Start = 0;
    if(ball1.position.x >=3)
    {
      Sfo1Start = 1;
    }
    if ( Sfo1Start )
    {
      Sfo1.tick();
    }
    // ball2.tick();
    // coin.tick();
    for (int i=0; i<4; i++)
    {
      coins[i].tick();
    }
    for (int i=0; i<4; i++)
    {
      doublecoins[i].tick();
    }
    camera_rotation_angle += 1;
    for (int i=0; i<4; i++)
    {
      if(detect_collision(ball1.bounding_box(),coins[i].bounding_box())) // coins yellow
      {
        coins[i].set_position(-100,-100);
      }
    }
    for (int i=0; i<4; i++)
    {
      if(detect_collision(ball1.bounding_box(),doublecoins[i].bounding_box())) // coins red
      {
        doublecoins[i].set_position(-100,-100);
      }
    }
    if(under_magnet_influence(ball1.bounding_box(),magnet.bounding_box())) // magnet
    {
      if (magnet.position.x > ball1.position.x )
      {
        ball1.position.x += 0.003;
        pointx += 0.003;
      }
      else if (magnet.position.x < ball1.position.x )
      {
        ball1.position.x -= 0.003;
        pointx -= 0.003;
      }
      if (magnet.position.y > ball1.position.y )
      {
        ball1.position.y += 0.003;
      }
      else if (magnet.position.y < ball1.position.y )
      {
        ball1.position.y -= 0.003;
      }
      if ( (abs(magnet.position.x - ball1.position.x)) <= magnetdisappear && (abs(magnet.position.y - ball1.position.y ) <= magnetdisappear))
      {
        magnet.set_position(-100,-100);
      }// tickcounter++;
    }
    if (detect_collision(ball1.bounding_box(),Sfo1.bounding_box()))
    {
      Sfo1.set_position(-100, -100);
    }
    // if (det)
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    int ycordcoin = createrandforcoin();
    ball1       = Ball(0, -2, COLOR_ORANGE);
    int start = -2;
    int doublestart = 8;
    for (int i=0; i<4; i++)
    {
      coins[i] = Coins(start,createrandforcoin(),COLOR_YELLOW);
      start++;
    }
    for (int i=0; i<4; i++)
    {
      doublecoins[i] = Coins(doublestart,createrandforcoin(),COLOR_DARKRED);
      doublestart++;
    }
    magnet = Magnet(3, 2, COLOR_DARKGREY);
    // coin        = Coins(2, ycordcoin, COLOR_YELLOW);
    // ball2       = Ball(-2, 0, COLOR_GREEN);
    // ball2.speed *= -1;
    Sfo1 = Sfo(7, 3, COLOR_WHITE);
    Firebeam1 = Firebeam (13, -3, COLOR_RED);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_GREY.r / 256.0, COLOR_GREY.g / 256.0, COLOR_GREY.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

/*bool detect_collision (Ball a, Ball b)
{
  float width = 2;
  return (abs(a.position.x - b.position.x) < width);
}*/

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    // printf ("True");
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // pointx += 0.005;
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        /*if (detect_collision(ball1, ball2))
        {
          ball1.speed *= -1;
          ball2.speed *= -1;
        };*/
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

/*bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}*/

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
