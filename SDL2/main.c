#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SDL_ExitWithError(const char *message);
void SDL_limitFPS(unsigned int limit);

/*
Pour compiler : gcc main.c $(sdl2-config --cflags --libs) -o prog
*/

int main(int argc, char *argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	unsigned int frame_limit = 0;
	frame_limit = SDL_GetTicks() + 16;
	

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) !=0) {
		SDL_ExitWithError("Initialisation SDL");
	}
	
	//Execution du programme

	if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) !=0)
		SDL_ExitWithError("Impossible de creer la fenetre et le rendu");
	
	//..................................................................

	SDL_Rect bouton ; //Bouton Bravo !
	bouton.x = 100;
	bouton.y = 100;
	bouton.w = 100;
	bouton.h = 50 ;

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(renderer, &bouton);

	SDL_Rect boutonp ;
	boutonp.x = 100;
	boutonp.y = 100;
	boutonp.w = 100;
	boutonp.h = 50;


	SDL_Rect quittt ; //Bouton Quitter
	quittt.x = 300;
	quittt.y = 200;
	quittt.w = 100;
	quittt.h = 50 ;

	SDL_SetRenderDrawColor(renderer, 250, 100, 100, 255);
	SDL_RenderFillRect(renderer, &quittt);

	SDL_Rect quitttp ;
	quitttp.x = 300;
	quitttp.y = 200;
	quitttp.w = 100;
	quitttp.h = 50;



	SDL_RenderPresent(renderer);



	SDL_bool program_launched = SDL_TRUE ;

	while(program_launched)
	{

		SDL_Event event;
		
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{

				case SDL_MOUSEBUTTONDOWN :
					if(event.button.x >= 100 && event.button.x <= 200 && event.button.y >= 100 && event.button.y <= 150){
						SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
						SDL_RenderFillRect(renderer, &boutonp);				
						SDL_RenderPresent(renderer);
					} else if(event.button.x >= 300 && event.button.x <= 400 && event.button.y >= 200 && event.button.y <= 250){
						SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
						SDL_RenderFillRect(renderer, &quitttp);
						SDL_RenderPresent(renderer);
						program_launched = SDL_FALSE;
					}
					break;

				case SDL_MOUSEBUTTONUP :
					SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
					SDL_RenderFillRect(renderer, &bouton);
					SDL_SetRenderDrawColor(renderer, 250, 100, 100, 255);
					SDL_RenderFillRect(renderer, &quittt);
					SDL_RenderPresent(renderer);
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
				default:
					break;
			}
		}

	}


	
	
	


	//..................................................................
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS; //return 0;
}

void SDL_ExitWithError(const char *message) {
	SDL_Log("ERREUR : %s > %s\n", message,SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}


void SDL_LimitFPS(unsigned int limit){
	unsigned int ticks = SDL_GetTicks();

	if(limit < ticks)
		return;
	else if(limit > ticks + 16)
		SDL_Delay(16);
	else 
		SDL_Delay(limit - ticks);
}
