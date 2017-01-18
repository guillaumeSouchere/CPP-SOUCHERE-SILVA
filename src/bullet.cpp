#include "bullet.h"
//constructeur
Bullet::Bullet(SDL_Surface* i) {
  image = i;
  dx = dy = x = y= xmove = ymove = 0;
}
//constructeur
Bullet::Bullet(SDL_Surface* i, int x_, int y_) {
  image = i;
  x = x_;
  y = y_;
  dx = dy = xmove = ymove = 0;
}
//constructeur
Bullet::Bullet(SDL_Surface* i, int x_, int y_, int dx_, int dy_) {
  image = i;
  x = x_;
  y = y_;
  xmove = dx_;
  ymove = dy_;
  dx = dy = 0;
}
//fonction de déplacement des balle 49-3
void Bullet::move() {
		x += xmove;
		y += ymove;
		dx += xmove;
		dy += ymove;
}
//fonction d'affichage
void Bullet::draw(SDL_Surface* s) {
  ApplySurface(x, y, image, s);
}

