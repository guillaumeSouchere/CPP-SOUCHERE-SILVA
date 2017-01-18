#include "background.h"
//constructeur
Background::Background(SDL_Surface* s) {
  image = s;
  x = y= x_ = y_ = 0;
  w = s->w;
  h = s->h;
}
//fonction faisant défiler le fond d'ecran
void Background::scroll() {
  x -= Background::step;
  if(x <= -w) {
    this->reset();
  }
}
//fonction de restet de la position du background
void Background::reset() {
  x = x_;
  y = y_;
}
//fonction d'affichage du bakground
void Background::draw(SDL_Surface* screen) {
  ApplySurface(x, y, image, screen);
  if(x <= -w + WIDTH) {
    ApplySurface(x + w, y, image, screen);
  }
}
