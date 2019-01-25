#include "main.h"
#include "timer.h"
#include "ball.h"
#include "coins.h"
#include "magnet.h"
#include "fireline60.h"
#include "sfo.h"
#include "fireline.h"
#include "fireline120.h"
#include "firebeam.h"
#include "platform.h"
#include "hump.h"
#include "boomerang.h"
#include "smarten.h"
#include "rocket.h"
#include "rocketRight.h"
#include "waterballoons.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
Platform platform;
Boomerang boomerang;
Hump hump;
Smarten smarten;
Sfo Sfo1;
int counter = 0;
int rightcounter = 0;
int leftcounter = 0;
Firebeam Firebeam1;
Firebeam60 fireline601;
Firebeam120 fireline1201;
doubleFirebeam doublebeam;
Rocket rocket[2];
RocketRight rocketRight[2];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float pointx = -3;
float pointy = 2;
float zoom = 1;
Waterballoons waterballoon[2];
int tickcounter = 0;
int magnetdisappear = 0;
int shoot[2] = {0};
int rocketCounter = -1;
int currentRocket = 0;
int rocketRightCounter = -1;
int currentRocketRight = 0;
int shootRight[2] = {0};
int Sfocounter = 0;
int waterballoonActivate1 = 0;
int waterballoonActivate2 = 0;
int waterballooncounter1 = 0;
int waterballooncounter2 = 0;
// int ycordcoin = rand() % 7 - 3; // -3 to 3
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
int createrandforcoin() {
  return ( rand() % 4  );
}
int createrandformagnet() {
  return ( rand() % 2 + 1);
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
    // waterballoon[1].draw(VP);
    waterballoon[0].draw(VP);
    ball1.draw(VP);
    platform.draw(VP);
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
    Sfo1.draw(VP);
    Firebeam1.draw(VP);
    fireline601.draw(VP);
    fireline1201.draw(VP);
    doublebeam.draw(VP);
    hump.draw(VP);
    boomerang.draw(VP);
    smarten.draw(VP);
    for(int i=0;i<2;i++)
    {
      rocket[i].draw(VP);
      rocketRight[i].draw(VP);
    }
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs((a.x) - (b.x)) * 1 < (a.width + b.width)) &&
           (abs((a.y) - (b.y)) * 1 < (a.height + b.height));
}
bool under_magnet_influence(bounding_box_t player, bounding_box_t magnet) {
    return (abs((player.x) - (magnet.x)) < (player.width  + magnet.width)*4) &&
           (abs((player.y) - (magnet.y)) < (player.height + magnet.height)*4);
}
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int top   = glfwGetKey(window, GLFW_KEY_UP);
    int waterballoonshoot = glfwGetKey(window, GLFW_KEY_S);
    if(waterballoonshoot&&waterballoonActivate2==1)
    {
      // waterballoonActivate2=1;
    }
    else if(waterballoonshoot&&waterballoonActivate1==1)
    {
      waterballoonActivate2=1;
    }
    if(waterballoonshoot&&waterballoonActivate1==0)
    {
      waterballoonActivate1=1;
    }

    if (left) {
        // Do something
        rightcounter = 0;
        leftcounter = 300;
        ball1.position.x -= 0.04;
        platform.position.x -= 0.04;
        pointx -= 0.04;
        if (detect_collision(ball1.bounding_box(),hump.bounding_box()))
        {
          if (ball1.position.x <= 8.7) {
            ball1.position.y += 0.04;
          }
          if (ball1.position.x <= 8.55) {
            ball1.position.y -= 0.01;
          }
          if (ball1.position.x <= 6.9) {
            ball1.position.y -= 0.01;
          }
          if (ball1.position.x <= 6.3) {
            ball1.position.y -= 0.04;
          }
        }
    }
    if (right) {
      leftcounter = 0;
      rightcounter = 300;
      platform.position.x += 0.04;
      ball1.position.x += 0.04;// change the ball's position so that it stays still but the rest is moving
      pointx += 0.04;//change the point you are looking
      if (detect_collision(ball1.bounding_box(),hump.bounding_box()))
      {
        ball1.position.y += 0.04;
        if (ball1.position.x > 4.6 && ball1.position.x < 7.5) {
          ball1.position.y -= 0.01;
        }
        if (ball1.position.x >= 7.5) {
          ball1.position.y -= 0.02;
        }
        if (ball1.position.x >= 7.8 && ball1.position.y >= -3.0) {
          ball1.position.y -= 0.04;
        }
      }
    }
    if (top) {
      counter = 0;
      if (detect_collision(ball1.bounding_box(),hump.bounding_box())) // top button can't work
      {
        // ball1.position.y += 0.04;
      }
      else if (ball1.position.y < 3)
      {
          ball1.position.y += 0.04;
      }
      if(rightcounter>0)
      {
        rightcounter-=100;
      }
      if(leftcounter>0)
      {
        leftcounter-=100;
      }
    }
    else if (!under_magnet_influence(ball1.bounding_box(),magnet.bounding_box())&&!detect_collision(ball1.bounding_box(),hump.bounding_box())) // this is gravity pulling down after the magnet has pulled the player up
    {
      if (ball1.position.y >= -3.0)
      {
          counter ++;
          ball1.position.y -= counter*0.004;//gravity
          if(rightcounter > 0)
          {
            platform.position.x += 0.04;
            ball1.position.x += 0.04;// change the ball's position so that it stays still but the rest is moving
            pointx += 0.04;//change the point you are looking
            if (detect_collision(ball1.bounding_box(),hump.bounding_box()))
            {
              ball1.position.y += 0.04;
              if (ball1.position.x > 4.6 && ball1.position.x < 7.5) {
                ball1.position.y -= 0.01;
              }
              if (ball1.position.x >= 7.5) {
                ball1.position.y -= 0.02;
              }
              if (ball1.position.x >= 7.8 && ball1.position.y >= -3.0) {
                ball1.position.y -= 0.04;
              }
            }
            rightcounter--;
          }
          else if (leftcounter > 0)
          {
            ball1.position.x -= 0.04;
            platform.position.x -= 0.04;
            pointx -= 0.04;
            if (detect_collision(ball1.bounding_box(),hump.bounding_box()))
            {
              if (ball1.position.x <= 8.7) {
                ball1.position.y += 0.04;
              }
              if (ball1.position.x <= 8.55) {
                ball1.position.y -= 0.01;
              }
              if (ball1.position.x <= 6.9) {
                ball1.position.y -= 0.01;
              }
              if (ball1.position.x <= 6.3) {
                ball1.position.y -= 0.04;
              }
            }
            leftcounter--;
          }
      }
      else
      {
        ball1.position.y = -3.01;
        counter = 0;
        rightcounter = 0;
        leftcounter = 0;
      }
    }
}


void tick_elements() {
    ball1.tick();
    magnet.tick();
    bool Sfo1Start = 0;
    if(ball1.position.x >= -1)
    {
      Sfo1Start = 1;
    }
    if ( Sfo1Start )
    {
      Sfo1.tick();
      if(Sfo1.position.y >= -2.8)
      {
        Sfocounter++;
        Sfo1.position.y -= Sfocounter*0.001;
      }
    }
    for (int i=0; i<4; i++)
    {
      coins[i].tick();
    }
    for (int i=0; i<4; i++)
    {
      doublecoins[i].tick();
    }
    fireline601.tick();
    fireline1201.tick();
    doublebeam.tick();
    boomerang.tick();
    smarten.tick();
    for(int i=0;i<2;i++)
    {
      if(shoot[i]==1)
      {
        rocket[i].tick();
        // printf("SHot%d\n",i);
        shoot[i]=1;
      }
      else if(((ball1.position.x > 29)&&(i==currentRocket)&&(rocketCounter < 0)&&(ball1.position.x < 34))) {
        currentRocket++;
        shoot[i]=1;
        rocket[i].tick();
      }
      if((ball1.position.x > 29)&&(rocketCounter < 0)&&(ball1.position.x < 34))
      {
        rocketCounter = 200;
      }
      // printf("%d--rocket\n",rocketCounter);
      rocketCounter--;
    }
    for(int i=0;i<2;i++) // for right rocket
    {
      if(shootRight[i]==1)
      {
        rocketRight[i].tick();
        shootRight[i]=1;
      }
      else if(((ball1.position.x > 34)&&(i==currentRocketRight)&&(rocketRightCounter < 0))) {
        currentRocketRight++;
        shootRight[i]=1;
        rocketRight[i].tick();
      }
      if((ball1.position.x > 34)&&(rocketRightCounter < 0))
      {
        rocketRightCounter = 200;
      }
      rocketRightCounter--;
    }
    camera_rotation_angle += 1;
    for(int i=0;i<2;i++)
    {
      if(shoot[i]==0)
      {
        rocket[i].position.y = smarten.position.y;
      }
      if(shootRight[i]==0)
      {
        rocketRight[i].position.y = smarten.position.y;
      }
    }
    if(waterballoonActivate1 ==  0)
    {
      waterballoon[0].position.y = ball1.position.y;
      waterballoon[0].position.x = ball1.position.x;
    }
    for (int i=0; i<4; i++)
    {
      if(detect_collision(ball1.bounding_box(),coins[i].bounding_box())) // coins yellow
      {
        coins[i].set_position(-100,-100);
        ball1.score += 5;
      }
    }
    for (int i=0; i<4; i++)
    {
      if(detect_collision(ball1.bounding_box(),doublecoins[i].bounding_box())) // coins red
      {
        doublecoins[i].set_position(-100,-100);
        ball1.score += 10;
      }
    }
    for (int i=0; i<2;i++)
    {
      if(detect_collision(ball1.bounding_box(),rocket[i].bounding_box())&&rocket[i].position.x!=32.75)
      {
        rocket[i].set_position(-100,-100);
        ball1.lives--;
      }
    }
    for (int i=0; i<2;i++)
    {
      if(detect_collision(ball1.bounding_box(),rocketRight[i].bounding_box())&&rocketRight[i].position.x!=33.25)
      {
        rocketRight[i].set_position(-100,-100);
        ball1.lives--;
      }
    }
    if(under_magnet_influence(ball1.bounding_box(),magnet.bounding_box())) // magnet
    {
      if (magnet.position.x > ball1.position.x )
      {
        // ball1.position.x += 0.003;
        ball1.speedx += 0.0001;
        pointx += ball1.speedx;
      }
      else if (magnet.position.x < ball1.position.x )
      {
        // ball1.position.x -= 0.003;
        ball1.speedx -= 0.0001;
        pointx -= ball1.speedx;
      }
      if (magnet.position.y > ball1.position.y )
      {
        // ball1.position.y += 0.003;
        platform.speedy += 0.0001;
        ball1.speedy += 0.0001;
      }
      else if (magnet.position.y < ball1.position.y )
      {
        // ball1.position.y -= 0.003;
        platform.speedy -= 0.0001;
        ball1.speedy -= 0.0001;
      }
      if ( (abs(magnet.position.x - ball1.position.x)) <= magnetdisappear && (abs(magnet.position.y - ball1.position.y ) <= magnetdisappear))
      {
        ball1.speedx = 0;
        ball1.speedy = 0;
        platform.speedy = 0;
        platform.speedx = 0;
        magnet.set_position(-100,-100);
      }// tickcounter++;
    }
    if (detect_collision(ball1.bounding_box(),Sfo1.bounding_box()))
    {
      Sfo1.set_position(-100, -100);
      ball1.score += 50;
    }
    if (detect_collision(ball1.bounding_box(),fireline1201.bounding_box()))
    {
      if ( ball1.position.x < 25.3 && ball1.position.y < -1.20 && ball1.position.x > 24.75 ) { // down 1 25 -1.5
        // Do nothing
      }
      else if ( ball1.position.x <= 24.75 && ball1.position.y < -0.90 && ball1.position.x > 24.25 ) { // down 1 25 -1.5
        // Do nothing
      }
      else if ( ball1.position.x <= 24.25 && ball1.position.y < -0.65 && ball1.position.x > 23.75 ) { // down 1 25 -1.5
        // Do nothing
      }
      else if ( ball1.position.x <= 23.75 && ball1.position.y < -0.10 && ball1.position.x > 22.75 ) { // down 1 25 -1.5
        // Do nothing
      }
      else if ( ball1.position.x > 25.3 && ball1.position.y > 1.65 && ball1.position.x < 26.6 ) {

      }
      else if ( ball1.position.x >= 26.6 && ball1.position.y > 1.20 && ball1.position.x < 27.5) {

      }
      else {
        fireline1201.set_position(-100, -100);
        printf("Dead2\n");
        ball1.lives--;
      }

    }
    if (detect_collision(ball1.bounding_box(),fireline601.bounding_box()))
    {
      if (ball1.position.x > 14 && ball1.position.y > 0.22 && ball1.position.x < 15.2) {
        // Do Nothing
      }
      else if(ball1.position.x > 15.8 && ball1.position.y < -1.50 && ball1.position.x < 16.2 ) { // down1
        // Do Nothing
      }
      else if(ball1.position.x > 16.2 && ball1.position.y < -1.25 && ball1.position.x < 17.6 ) { // down2
        // Do Nothing
      }
      else {
        fireline601.set_position(-100, -100);
        ball1.lives--;
      }
    }
    if (detect_collision(ball1.bounding_box(),doublebeam.bounding_box()))
    {
      doublebeam.set_position(-100, -100);
      ball1.lives--;
    }
    if (detect_collision(ball1.bounding_box(),Firebeam1.bounding_box()))
    {
      Firebeam1.set_position(-100, -100);
      ball1.lives--;
    }
    if (detect_collision(ball1.bounding_box(),hump.bounding_box()))
    {
      // ball1.position.y += 0.04;
      // printf("genie\n");
    }
    if (detect_collision(waterballoon[0].bounding_box(),fireline601.bounding_box()))
    {
      waterballoon[0].set_position(-100,-100);
      fireline601.set_position(-100,-100);
    }
    if (detect_collision(waterballoon[0].bounding_box(),fireline1201.bounding_box()))
    {
      waterballoon[0].set_position(-100,-100);
      fireline1201.set_position(-100,-100);
    }
    if (detect_collision(waterballoon[0].bounding_box(),Firebeam1.bounding_box()))
    {
      waterballoon[0].set_position(-100,-100);
      Firebeam1.set_position(-100,-100);
    }
    if(boomerang.position.y < -3) {
      boomerang.speedx = 0;
      boomerang.speedy = 0;
      boomerang.accx = 0;
      boomerang.set_position(-100,-100);
    }
    if (detect_collision(ball1.bounding_box(),boomerang.bounding_box()))
    {
      boomerang.speedx = 0;
      boomerang.speedy = 0;
      boomerang.accx = 0;
      boomerang.set_position(-100,-100);
      ball1.lives--;
    }
    if(smarten.position.y > ball1.position.y)
    {
      smarten.position.y -= 0.04;
      if(smarten.position.y < -2.5)
      {
        smarten.position.y = -2.5;
      }
    }
    else if (smarten.position.y == ball1.position.y)
    {// do Nothing

    }
    else
    {
      smarten.position.y += 0.04;
    }
    if(waterballoonActivate1==1)// first ballon activated
    {
      waterballoon[0].tick();
      waterballooncounter1 ++;
      if(waterballoon[0].position.y > -3.5)
      {
        waterballoon[0].position.y -= waterballooncounter1*0.0004;//gravity
      }
      else
      {
        waterballoon[0].set_position(-100,-100);
      }
    }
    // cout << ball1.position.x + ',' + ball1.position.y << endl;
    // printf("%f , %f\n", ball1.position.x, ball1.position.y);
    // printf("%f ,%f\n", waterballoon[0].position.x, waterballoon[0].position.y);
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // int ycordcoin = createrandforcoin();
    ball1         = Ball(-4, -2, COLOR_ORANGE);
    platform      = Platform(0, -5.5, COLOR_DARKGREY);
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
    magnet = Magnet(6, 2, COLOR_DARKGREY);
    Sfo1 = Sfo(4, 3, COLOR_WHITE);
    Firebeam1 = Firebeam (13, -3, COLOR_RED);
    fireline601 = Firebeam60 ( 15, -1, COLOR_RED);
    fireline1201 = Firebeam120 ( 24, -1, COLOR_RED);
    doublebeam = doubleFirebeam ( 20, -1, COLOR_RED);
    hump = Hump(7, -3.5 , COLOR_DARKGREY);
    boomerang = Boomerang(-3, 0, COLOR_RED);
    smarten = Smarten(33, 0, COLOR_RED);
    for(int i = 0; i<2; i++)
    {
      rocket[i] = Rocket(32.75,0,COLOR_RED);
    }
    for(int i = 0; i<2; i++)
    {
      rocketRight[i] = RocketRight(33.25,0,COLOR_RED);
    }
    for(int i = 0;i<1;i++)
    {
      waterballoon[i] = Waterballoons(ball1.position.x, ball1.position.y, COLOR_BLUE);
    }
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
            if (ball1.lives < 0)
            {
              break;
            }
            char stingy[100];
            sprintf(stingy,"Score is %d and lives left is %d",ball1.score,ball1.lives);
            glfwSwapBuffers(window);
            glfwSetWindowTitle(window,stingy);
            tick_elements();
            tick_input(window);
            // printf("%f %f\n", ball1.position.x, ball1.position.y);
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
