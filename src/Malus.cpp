#include "malus.h"

Malus::Malus(std::string name, int x, int y) : Obstacle(name, x, y){}

Malus::~Malus() {}

//fonction qui permet de traiter les differentes possibilités d'interaction entre
//joueur et les malus
void Malus::reactToPlayer(Character* c) {
	int index = -1;

	index = hit(c->bullets);


	// une balle du joueur rencontre un des obstacle malus
  	if (index != -1) {
  		c->bullets.erase(c->bullets.begin() + index);
  		for (int i = malus.size() - 1; i >= 0; i--){
  			malus[i].life -= BULLET_DAMAGE;
  			// si la vie d'un obstacle est négative ou nulle 
  			if (!malus[i].alive()) {
  				malus.erase(malus.begin() + i);
  			}
  		}
  	}
  	//le joueur lui meme rencontre un des obstacles malus
  	if (c->immunite){
  		c->immunite--;
  	}
  	else{
	  	for (int i = malus.size() - 1; i >= 0; i--){
	  		if (((c->getX() + CHARACTER_WIDTH / 2) >= malus[i].x) && (c->getX() + CHARACTER_WIDTH / 2) <= malus[i].x + OBSTACLE_WIDTH) {
	  			if (((c->getY() + CHARACTER_HEIGHT / 2) >= malus[i].y) && (c->getY() <= malus[i].y + OBSTACLE_WIDTH)) {
	  				c->life -= OBSTACLE_DAMAGE;
	  				c -> immunite = 24;//immuite 1s
	  				malus[i].state = oDeathState;
	  			}
	  		} 
	  	} 
	}
  	// dans tout les cas, on déplace les obstacles malus restants
  	for (int i = malus.size() - 1; i >= 0; i--){
 		malus[i].x -= OBSTACLE_STEP;
  	} 
}
// test : une belle touche une enveloppe
int Malus::hit(std::vector<Bullet> b) { 
			
	for (int i = b.size() - 1; i >= 0; i--){
    for (int j = malus.size() - 1; j >= 0; j--) {
  		if ( b[i].getX() + 60 >= malus[j].x && b[i].getX() + 60 <= malus[j].x + 96){
  			if (b[i].getY() >= malus[j].y)
  				return i;
  		}
    }
	}
	return -1;
}
// fonction d'affichage de tous les element du vecteur de malus
void Malus::draw(SDL_Surface * screen) {
    int frame1, state1;  
    SDL_Rect clip;
	for (int i = malus.size() - 1; i >= 0; i--) {
		frame1 = static_cast<int>(this->frame);
		state1 = static_cast<int>(this->state);
		clip = malus[i].clips[state1][frame1];
		ApplySurface(malus[i].x, malus[i].y, image, screen, &clip);
		
	}
}
// ajout d'un malus dans le vecteur malus
void Malus::add() {
	malus.push_back(Malus("malus", WIDTH - OBSTACLE_WIDTH, HEIGHT - OBSTACLE_HEIGHT));
}