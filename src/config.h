#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Game config */
#define WIDTH            700
#define HEIGHT           400
#define DEPTH            32
#define WINDOW_TITLE     "A Game"

#define FPS              30
#define GRAVITY          1.7  
#define Y_VELOCITY_STEP  -20

#define FRAME_STEP       0.4

/* Character */
#define CHARACTER_WIDTH  96
#define CHARACTER_HEIGHT 96

#define CHARACTERMENU_WIDTH 200
#define CHARACTERMENU_HEIGHT 305

#define CHARACTER_BACK   0x00, 0x80,0x00
#define CHARACTER_STEP   5

#define REST_INDEX       0
#define WALK_RIGHT_INDEX 1
#define JUMP_RIGHT_INDEX 2
#define SLIDE_INDEX	     3
#define DEATH_INDEX 	 4
#define WALK_LEFT_INDEX	 5
#define JUMP_LEFT_INDEX	 6

#define NUMSTATES        7

#define BULLET_SPEED     15
#define BULLET_DELAY     200
#define BULLET_DAMAGE    1

/* Obstacle */
#define OBSTACLE_WIDTH     50
#define OBSTACLE_HEIGHT    96
#define OBSTACLE_STEP      5

#define OREST_INDEX      0
#define ODEATH_INDEX     1

#define ONUMSTATES       2

#define OBSTACLE_DAMAGE  1

#endif /* _CONFIG_H_ */
