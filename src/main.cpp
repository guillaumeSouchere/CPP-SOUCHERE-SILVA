#include "game.h"
#include "character.h"
#include "music.h"
#include "fog.h"
#include "background.h"
#include "obstacle.h"
#include "malus.h"

#include <vector>

int main(int argc, char** argv) {
  int deplacement = 0;
  Timer fps;

  bool quit = false, win = false, first = true, play = false;

  SDL_Surface *screen = InitSDL();
  Background background(LoadImage("data/back.png", true));
  Background backgroundMenu(LoadImage("data/backmenu.png", true));
  Background winImage(LoadImage("data/win.png", true));
  Background loseImage(LoadImage("data/lose.png", true));
  Background playImage(LoadImage("data/play.png", true));
  Fog fog(LoadImage("data/fog.png", true));
  fog.setXY(0, 300);
  
  Music::init();
  Music music("data/music.ogg");
  music.loop();

  SDL_Event event;
 

  Character player("character", WIDTH / 6 - CHARACTER_WIDTH / 2, HEIGHT - CHARACTER_HEIGHT);
  Character playerMenu("characterMenu", CHARACTER_WIDTH / 2, HEIGHT - CHARACTERMENU_HEIGHT);
  Malus malus("malus", WIDTH - OBSTACLE_WIDTH, HEIGHT - OBSTACLE_HEIGHT);
  malus.add();

  bool keys[256];
  for(int i = 0; i < 256; ++i) {
    keys[i] = false;
  }

  backgroundMenu.draw(screen);
  playerMenu.draw(screen);
  fog.draw(screen);

  	while (!quit) {

	    while(!play && !quit) {
	    	fps.start();

	  		playerMenu.nextFrame();
	  		fog.scroll();

	  		backgroundMenu.draw(screen);
		    playerMenu.draw(screen);
		    if (win) {
		    	winImage.draw(screen);
		    }
		    if (!win && !first) {
		    	loseImage.draw(screen);
		    }
		    fog.draw(screen);
		    playImage.draw(screen);
		    SDL_Flip(screen);

		    if(fps.getTicks() < 1000 / FPS) {
		    	SDL_Delay((1000 / FPS) - fps.getTicks());
		    }

		    while (SDL_PollEvent(&event)) {
		    	switch(event.type) {
		    		case SDL_KEYDOWN:
		    			if (event.key.keysym.sym == SDLK_RETURN)
				    		play = true;
				    	break;
		    		case SDL_QUIT:
		    			quit = true;
		    			break;
		    		default :
		    			break;
		    	}
		    }
	    }
	    first = false;
	      
	    for(int i = 0; i < 256; ++i) {
    		keys[i] = false;
    	}  

	    int i = 0;
	    while(play && !quit) {
	  		fps.start();

		    //A virer
		    i++;
		    if(i >= 50){
		    	malus.add();
		    	i = 0;
		    }
 
		    while(SDL_PollEvent(&event)) {
		      switch(event.type) {
		        case SDL_QUIT:
			  quit = true;
			  break;
		        case SDL_KEYDOWN:
			  keys[event.key.keysym.sym] = true;
			  break;
		        case SDL_KEYUP:
			  keys[event.key.keysym.sym] = false;
			  break;
		      }
		    }
		    player.handleKeys(keys);

		    if(player.getX() < 0) {
		      player.setX(0);
		    } 
		    else if(player.getX() > WIDTH - CHARACTER_WIDTH) {
		      player.setX(WIDTH - CHARACTER_WIDTH);
		    }

		    if(keys[SDLK_RIGHT] && player.getX() >= (WIDTH / 6) - (CHARACTER_WIDTH / 2) + deplacement) {
		      deplacement++;
		      background.scroll();
		      player.setX((WIDTH / 6) - (CHARACTER_WIDTH / 2) + deplacement);
		    }

		    player.nextFrame();
		    malus.nextFrame(); 
		    malus.reactToPlayer(&player);  

		    fog.scroll();

		    background.draw(screen);
		    fog.draw(screen);
		    malus.draw(screen);
		    player.draw(screen);

		    SDL_Flip(screen);
		    
		    if(fps.getTicks() < 1000 / FPS) {
		      SDL_Delay((1000 / FPS) - fps.getTicks());
		    }

			if (!player.alive()) {

				win = false;
				play = false;
				deplacement = 0;
				player.characterInit();
				player.setX(WIDTH / 6 - CHARACTER_WIDTH / 2);
				player.setY(HEIGHT - CHARACTER_HEIGHT);
				
				for (int i = malus.malus.size() - 1; i >= 0; i--) {
					malus.malus.erase(malus.malus.begin() + i);
				}
				for (int i = player.bullets.size() - 1; i >= 0; i--) {
					player.bullets.erase(player.bullets.begin() + i);
				}

				if(fps.getTicks() < 50000 / FPS) {
			        SDL_Delay((50000 / FPS) - fps.getTicks());
			    }
			}
			
			if (player.getX() >= WIDTH - CHARACTER_WIDTH) {
				win = true;
				play = false;
				deplacement = 0;
				player.characterInit();
				player.setX(WIDTH / 6 - CHARACTER_WIDTH / 2);
				player.setY(HEIGHT - CHARACTER_HEIGHT);

				for (int i = malus.malus.size() - 1; i >= 0; i--) {
					malus.malus.erase(malus.malus.begin() + i);
				}

				for (int i = player.bullets.size() - 1; i >= 0; i--) {
					player.bullets.erase(player.bullets.begin() + i);
				}
				
				if(fps.getTicks() < 50000 / FPS) {
			        SDL_Delay((50000 / FPS) - fps.getTicks());
			    }

				break;
			}
		}
	    for(int i = 0; i < 256; ++i) {
    		keys[i] = false;
    	}
	}

  return CleanUp();
}
