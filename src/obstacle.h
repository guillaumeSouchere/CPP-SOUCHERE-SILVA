#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <iostream>
#include <fstream>

#include "bullet.h"
#include "game.h"
#include "character.h"
#include "timer.h"


class Obstacle {
protected:
  string name;
  int x, y;  
  const static int maxDistance = WIDTH;
  int life;
  
  double frame;
  int numframes[ONUMSTATES]; /* rest, death */
  
  ObstacleState state;

  SDL_Rect *clips[ONUMSTATES];
  SDL_Surface *image;

public:

  Obstacle(std::string, int, int); 
  Obstacle() {};
  ~Obstacle();
  
  bool load();
  //void draw(SDL_Surface*);
  int nextFrame();


  int getX() { return x; }
  int getY() { return y; }
  int getLife() {return life;}
  void setX(int v) { x = v; }
  void setY(int v) { y = v; }
  void setXY(int a, int b) { x = a; y = b; }
  
  bool alive() { return life > 0; }
  int health() { return life; }

};

#endif /* _OBSTACLE_H_ */
