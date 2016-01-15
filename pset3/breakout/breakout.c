//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Paddle with and Height and Location
#define PWIDTH 70
#define PHEIGHT 15
#define PADDLEX (WIDTH - PWIDTH)/2.0
#define PADDLEY HEIGHT-50*1.0

// brick width and height and y starting position
#define BWIDTH 36
#define BHEIGHT 12
#define BRICKY 70

// ball velocity

#define VELOCITY 0.5

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
    
    // intiate random velocity and y direction
    double velocity = drand48();
    double yball = 2.0;
    
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent cursor = getNextEvent(MOUSE_EVENT);
        
        move(ball, velocity, yball);
        
        // checks to see if ball hits a wall and reverses vector
        if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0 )
        {
            velocity = -velocity;
        }
        
        if (getY(ball) <= 0)
        {
            yball = -yball;
        }
        
        // checks if it ball hits an object
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle)
            {
                // using absolute value stops side paddle glitch
                yball = -fabs(yball);
            }
            
            // checks to see if object is a brick and adds to score if hit
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                points++;
                updateScoreboard(window, label, points);
                if (points == 50)
                {
                    break;
                }
                yball = -yball;
            }
        }
            
        // centers paddle with mouse and follows horizontal movement
        if (cursor != NULL)
        {
            if (getEventType(cursor) == MOUSE_MOVED)
            {
                double x = getX(cursor) - PWIDTH / 2 ;
                if ( x <= 0 )
                {
                    setLocation(paddle, 0, PADDLEY);
                }
                else if (x >= WIDTH - PWIDTH)
                {
                    setLocation(paddle, (WIDTH - PWIDTH), PADDLEY);
                }
                else
                {
                    setLocation(paddle, x, PADDLEY);
                }
            }
            
        }
        
        if (getY(ball) + getHeight(ball) >= getHeight(window) )
        {
            lives = lives - 1;
            if (lives == 0)
            {
                break;
            }
            waitForClick();
            setLocation(ball,WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS ); 
             
        }
        
        pause(5);
        
    }
    removeGWindow(window,ball);
    if (lives == 0)
    {
        setLabel(label, "GAME OVER");
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2;
        setLocation(label, x, y);  
    }
    
    if (points == 50)
    {
        setLabel(label, "YOU WIN");
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2;
        setLocation(label, x, y);  
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
    // set colour which is dependent on row
    char* colour[] = {"RED","ORANGE","YELLOW","GREEN","CYAN"};
    
    for (int i = 0; i < ROWS; i++)
    {        
        // fits 10 blocks with 2 pixel space at the ends
        for (int j = 0; j < COLS; j++)
        {
            GRect block = newGRect (2 + (40 * j),BRICKY + ((BHEIGHT + 4) * i),BWIDTH, BHEIGHT);
            setColor(block, colour[i]);
            setFilled(block, true); 
            add(window ,block );
        }
   
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval ( WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, 2 * RADIUS, 2 * RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(PADDLEX, PADDLEY, PWIDTH, PHEIGHT); 
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel ("");
    setFont(score, "SansSerif-36");
    updateScoreboard(window, score, 0);
    add(window,score);
    
    return score;
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


