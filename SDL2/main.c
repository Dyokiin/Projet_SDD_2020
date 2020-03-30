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
	

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) !=0) {  //Verification du chargement de la SDL
		SDL_ExitWithError("Initialisation SDL");
	}
	
	//Execution du programme

	if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) !=0)
		SDL_ExitWithError("Impossible de creer la fenetre et le rendu");
	
	//..................................................................

	SDL_bool program_launched = SDL_TRUE ;

	while(program_launched)
	{

		SDL_Event event;
		
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{

				case SDL_MOUSEBUTTONDOWN:
					printf("Clic en %dx / %dy\n", event.button.x, event.button.y);
					break;
				case SDL_MOUSEBUTTONUP:	
					printf("Declic en %dx / %dy\n", event.button.x, event.button.y);
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
s
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
