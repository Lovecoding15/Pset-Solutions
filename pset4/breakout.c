//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

//width of the paddle
#define PADDLE_W 70
#define PADDLE_H 10


// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // Ball speed is set to random
    double velocity_x = drand48()*2;
    double velocity_y = 2;
    
    updateScoreboard(window, label, points);
    
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
              
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor along the x-axis
                double x = getX(event)- getWidth(paddle)/2;
                                               
                setLocation(paddle, x, 530);
            }
        }
        
        move(ball, velocity_x, velocity_y);
        
         // linger before moving again
        pause(8);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_x = -velocity_x;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity_x= -velocity_x;
        }
        
        //bounce top edge of window
        else if (getY(ball) <= 0)
        {
            velocity_y= -velocity_y;
        }
        
        GObject object = detectCollision(window, ball);
        
         if (object != NULL)
        {
            // If it is the paddle, then flip the y velocity.
            if (object == paddle)
            {
                velocity_y = -velocity_y;
                
            }
            
            else if(strcmp(getType(object), "GRect") == 0)
            {
                velocity_y = -velocity_y;
                removeGWindow(window, object);
                points += 1 ;
                updateScoreboard(window, label, points);
                bricks--;
            }
        }
        
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            setLocation(ball,getWidth(window)/2, getHeight(window)/2);
            lives--;
            waitForClick(); 
        }

       
    }
          
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int x = 5, y = 50,i,j;
    
    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
               GRect bricks = newGRect(x,y,33,8);
               
               if(i == 0) 
               setColor(bricks, "RED");
               
               if(i == 1) 
               setColor(bricks, "MAGENTA");
               
               if(i == 2) 
               setColor(bricks, "BLUE");
               
               if(i == 3) 
               setColor(bricks, "GREEN");
               
               if(i == 4) 
               setColor(bricks, "YELLOW");

               setFilled(bricks,true);
               add(window,bricks);
               x+=40;
         }
         x=5;
         y+=12;
     }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = (getWidth(window) - 20) / 2;
    double y = (getHeight(window) - 20) / 2;
    GOval ball = newGOval(x,y, 20,20);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle= newGRect(170,530,PADDLE_W,PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle,"Black");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
