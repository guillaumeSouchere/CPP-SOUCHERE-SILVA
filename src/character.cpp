#include "game.h"
#include "character.h"

Character::Character(string n, int x_, int y_) {
  name = n;
  x = x_;
  y = y_;
  image = NULL;
  frame = 0;
  characterInit();

  bulletImage = LoadImage("data/bullet.png", true);

  if (n == "characterMenu") {
	  if(!this->load2()) {
	    FATAL("couldn't load character instance!");
	  }
  }
  else {
	  if(!this->load()) {
	    FATAL("couldn't load character instance!");
	  }  
  }
}

Character::~Character() {
  SDL_FreeSurface(image);
  SDL_FreeSurface(bulletImage);
}
// fonction qui charge un joueur lors de sa création dans la main
bool Character::load() {
  using namespace std;
  string charImage("data/" + this->name + ".png");
  string imageData(charImage + ".info");

  ifstream imageFile(charImage.c_str(), ios::binary);
  ifstream infoFile(imageData.c_str());

  if(!imageFile.is_open()) {
    cerr << "can't open image file: " << charImage << endl;
    return false;
  }
  if(!infoFile.is_open()) {
    cerr << "can't open info file: " << imageData << endl;
    return false;
  }

  image = LoadImage(charImage, true);
  if(image == NULL) {
    cerr << "error opening image file" << endl;
    return false;
  }

  int r, w, j, a, d, wl, jl;  
  infoFile >> r >> w >> j >> a >> d >> wl >> jl;
  numframes[REST_INDEX] = r;
  numframes[WALK_RIGHT_INDEX] = w;
  numframes[JUMP_RIGHT_INDEX] = j;
  numframes[SLIDE_INDEX] = a;
  numframes[DEATH_INDEX] = d;
  numframes[WALK_LEFT_INDEX] = wl;
  numframes[JUMP_LEFT_INDEX] = jl;

  for(int x = 0; x < NUMSTATES; x++) {
    int ctr = -1;
    switch(x) {
      case REST_INDEX:
	ctr = r;
	break;
      case WALK_RIGHT_INDEX:
	ctr = w;
	break;
      case JUMP_RIGHT_INDEX:
	ctr = j;
	break;
      case WALK_LEFT_INDEX:
	ctr = wl;
	break;
      case JUMP_LEFT_INDEX:
	ctr = jl;
	break;
      case SLIDE_INDEX:
	ctr = a;
	break;
	  case DEATH_INDEX:
	ctr = d;
	break;
    }
    SDL_Rect* tempptr = new SDL_Rect[ctr];
    for(int i = 0; i < ctr; i++) {
      SDL_Rect tmp;
      tmp.x = i * CHARACTER_WIDTH;
      tmp.y = x * CHARACTER_HEIGHT;
      tmp.w = CHARACTER_WIDTH;
      tmp.h = CHARACTER_HEIGHT;
      tempptr[i] = tmp;
    }
    clips[x] = tempptr;
  }

  return true;
}
//fonction qui initialise le character visible dans le menu de demarrage
bool Character::load2() {
	using namespace std;
	string charImage("data/" + this->name + ".png");

	ifstream imageFile(charImage.c_str(), ios::binary);

	if(!imageFile.is_open()) {
		cerr << "can't open image file: " << charImage << endl;
		return false;
	}

	image = LoadImage(charImage, true);
	if(image == NULL) {
		cerr << "error opening image file" << endl;
		return false;
	}

	numframes[REST_INDEX] = 10;
	numframes[WALK_RIGHT_INDEX] = 0;
	numframes[JUMP_RIGHT_INDEX] = 0;
	numframes[SLIDE_INDEX] = 0;
	numframes[DEATH_INDEX] = 0;
	numframes[WALK_LEFT_INDEX] = 0;
	numframes[JUMP_LEFT_INDEX] = 0;

	int ctr = 10;
	SDL_Rect* tempptr = new SDL_Rect[ctr];
	for(int i = 0; i < ctr; i++) {
	  SDL_Rect tmp;
	  tmp.x = i * CHARACTERMENU_WIDTH;
	  tmp.y = 0;
	  tmp.w = CHARACTERMENU_WIDTH;
	  tmp.h = CHARACTERMENU_HEIGHT;
	  tempptr[i] = tmp;
	}
	clips[0] = tempptr;

  return true;
}

void Character::draw(SDL_Surface* screen) {
  SDL_Rect clip1;
  int frame = static_cast<int>(this->frame);
  clip1 = clips[state][frame];
  ApplySurface(x, y, image, screen, &clip1);	

  for(int i = bullets.size() - 1; i >= 0; --i) {
    if(bullets[i].dx >= Bullet::MaxDistance) {
      bullets.erase(bullets.begin() + i);
    }
    bullets[i].move();
    bullets[i].draw(screen);
  }
}

int Character::nextFrame() {
  int frames = numframes[state];
  frame = frame + FRAME_STEP;
  if(this->frame >= frames) {
    frame = 0;
  }
  return (static_cast<int>(frame)) % frames;
}
//fonction chargé de gérer les différents cas de declenchement de
//l'event
void Character::handleKeys(const bool keys[]) {
  
  if(!alive()) {
	state = DeathState;
  }
  else {

	  if(keys[SDLK_SPACE]) {
	    atk = true;
	    if(SDL_GetTicks() - lastShot > BULLET_DELAY) {
	      this->fire();
	    }
	    atk = false;
	  }

	  if(keys[SDLK_UP] && !jumping) {
	    if (state == WalkRightState)
	    	state = JumpRightState;
	    else if (state == WalkLeftState)
	    	state = JumpLeftState;
	    else
	    	state = JumpRightState;
	    jumping = true;
	    velocity_y = Y_VELOCITY_STEP;
	    y += Y_VELOCITY_STEP;
	  }
	  if (keys[SDLK_DOWN] && !sliding && !jumping){
	  	state = DownState;
	  	sliding = true;
	  }

	  if(jumping) {
	    if(y + velocity_y < HEIGHT - CHARACTER_HEIGHT) {
	      y = y + velocity_y;
	      velocity_y = velocity_y + GRAVITY;
	    } else {
	      jumping = false;
	      velocity_y = 0;
	      y = HEIGHT - CHARACTER_HEIGHT;
	    }
	  }

	  if (sliding && !jumping) {
		if (!keys[SDLK_DOWN]) {
			sliding = false;
		}
	  }

	  if(!jumping && !atk && !sliding) {
	  	if (keys[SDLK_RIGHT]) {
	    	state = WalkRightState;
	    	x += CHARACTER_STEP;
	  	}
	    else if (keys[SDLK_LEFT]) {
	    	state = WalkLeftState;
	    	x -= CHARACTER_STEP;
	    }
	    else 
	    	state = RestState;
	  }
  }
}
//fonction ajoutant une balle dans le vecteur de balle 
//depend du temps
//en effet pour eviter le tir continu on oblige l fonction a ne créer la balle
//que lorsque un certain delta s'est écoulé
void Character::fire() {
  lastShot = SDL_GetTicks();
  bullets.push_back(Bullet(bulletImage, x + CHARACTER_WIDTH / 2,
			   y + CHARACTER_HEIGHT / 1.7, BULLET_SPEED, 0));
}
//fonction initialisant certan paramatres du character
// evite la redondance du code
void Character::characterInit() {
	state = RestState;
	life = 3;
	jumping = false;
	sliding = false;
	velocity_x = velocity_y = 0;
	immunite = 0;				

}

