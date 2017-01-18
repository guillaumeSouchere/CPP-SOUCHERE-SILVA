#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "game.h"

class Background {
  const static int step = 10;
private:
  SDL_Surface* image;
  int x, y, x_, y_;
  int w, h;
public:
  Background(SDL_Surface*);
  ~Background(){SDL_FreeSurface(image);}
  
  void scroll();
  void reset();
  void draw(SDL_Surface*);
};

#endif /* BACKGROUND_H_ */
