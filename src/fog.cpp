#include "fog.h"
//constructeur
Fog::Fog(SDL_Surface* s) {
  fog = s;
  x = y = x_ = y_ = 0;
  w = s->w;
  h = s->h;
}
//fonction de defilement du brouillard
void Fog::scroll() {
  x -= Fog::step;
  if(x <= -w) {
    this->reset();
  }
}
//fonction de reset de position de l'image du brouillard
void Fog::reset() {
  x = x_;
  y = y_;
}
//fonction d'affichage
void Fog::draw(SDL_Surface* screen) {
  ApplySurface(x, y - 200, fog, screen);
  if(x <= -w + WIDTH) {
    ApplySurface(x + w, y - 200, fog, screen);
  }
}
