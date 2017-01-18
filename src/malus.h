#ifndef _MALUS_H_
#define _MALUS_H_

#include "obstacle.h"

class Malus : public Obstacle {

public:
  std::vector<Malus> malus;

  int hit(std::vector<Bullet> b);

  Malus(std::string, int, int); 
  Malus() : Obstacle(){};
  ~Malus();
  void reactToPlayer(Character*);
  void draw(SDL_Surface *);
  void add(void);
};

#endif /* _MALUS_H_ */
