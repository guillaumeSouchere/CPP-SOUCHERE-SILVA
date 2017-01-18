#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "bullet.h"

#include <vector>
#include <fstream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Character {
private:
  string name;
  int x, y;
  double velocity_x, velocity_y;
  
  double frame;
  int numframes[NUMSTATES]; // rest, walk, jump, slide, death
  MoveState state;
  bool jumping = false;
  bool sliding = false;
  bool moved = false;
  bool atk = false;

  SDL_Rect *clips[NUMSTATES]; // rest, walk, jump, slide, death
  SDL_Surface *image;

public:
  int immunite;
  
  SDL_Surface *bulletImage;
  std::vector<Bullet> bullets;
  Uint32 lastShot = 0;
  int life;

  Character(std::string, int, int);
  Character() { };
  ~Character();
  bool load();
  bool load2();
  void characterInit(void);
  void draw(SDL_Surface*);
  int nextFrame();
  void handleKeys(const bool[]);
  int getFrame() {return frame;}
  MoveState getState() {return state;}
  int getX() { return x; }
  int getY() { return y; }
  void setX(int v) { x = v; }
  void setY(int v) { y = v; }
  void fire();

  void hit(int damage=OBSTACLE_DAMAGE) {life -= damage; }
  bool alive() { return life > 0; }
  int health() { return life; }
  void resetMoved(){moved = false;}
};

#endif /*_CHARACTER_H_*/
