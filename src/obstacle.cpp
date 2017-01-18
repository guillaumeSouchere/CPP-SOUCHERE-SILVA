#include "obstacle.h"

Obstacle::Obstacle(string n, int x_, int y_) {
  name = n;
  x = x_;
  y = y_;
  
  life = 2;
  frame = 0;
  image = NULL;
  state = oRestState;
  if(!this->load()) {
    FATAL("couldn't create obstacle instance!");
  }
}

Obstacle::~Obstacle() {}

//fonction de chargement des images liées aux obstacles
bool Obstacle::load() {
  using std::ifstream;
  string oImage("data/" + this->name + ".png");
  string imageData(oImage + ".info");

  ifstream imageFile(oImage.c_str(), std::ios::binary);
  ifstream infoFile(imageData.c_str());

  if(!imageFile.is_open()) {
    cerr << "can't open image file: " << oImage << endl;
    return false;
  }
  if(!infoFile.is_open()) {
    cerr << "can't open info file: " << imageData << endl;
    return false;
  }

  image = LoadImage(oImage, true);
  
  int r, d;
  infoFile >> r >> d;
  numframes[OREST_INDEX] = r;
  numframes[ODEATH_INDEX] = d;
  for(int i = 0; i < ONUMSTATES; ++i) {
    int ctr = -1;
    switch(i) {
      case OREST_INDEX: 
  	    ctr = r;
  	    break;
      case ODEATH_INDEX:
  	    ctr = d;
  	    break;
    }

    SDL_Rect* tmpptr = new SDL_Rect[ctr];
    for(int x = 0; x < ctr; ++x) {
      SDL_Rect tmp;
      tmp.x = x * OBSTACLE_WIDTH;
      tmp.y = i * OBSTACLE_HEIGHT;
      tmp.w = OBSTACLE_WIDTH;
      tmp.h = OBSTACLE_HEIGHT;
      tmpptr[x] = tmp;
    }
    clips[i] = tmpptr;
  }
  return true;  
}

//fonction qui charge la prochaine image à afficher pour realiser 
//l'effet d'animation
int Obstacle::nextFrame() {
  int frames = numframes[state];
  frame = frame + FRAME_STEP;
  if(this->frame >= frames) {
    frame = 0;
  }
  return (static_cast<int>(frame)) % frames;
}

