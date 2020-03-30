#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SDL_ExitWithError(const char *message);

/*
Pour compiler : gcc main.c $(sdl2-config --cflags --libs) -o prog
*/

int main(int argc, char *argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) !=0) {  //Verification du chargement de la SDL
		SDL_ExitWithError("Initialisation SDL");
	}
	
	//Execution du programme

	if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) !=0)
		SDL_ExitWithError("Impossible de creer la fenetre et le rendu");
	
	//..................................................................
	if(SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de creer la couleur pour le rendu") ;
	
	if(SDL_RenderDrawPoint(renderer, 100, 450) !=0)
		SDL_ExitWithError("Impossible de dessiner un point") ;

	if(SDL_SetRenderDrawColor(renderer, 255, 15, 15, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de creer la couleur pour le rendu") ;

	if(SDL_RenderDrawLine(renderer, 50, 50, 500, 500) !=0)
		SDL_ExitWithError("Impossible de dessiner une ligne") ;

	if(SDL_SetRenderDrawColor(renderer, 15, 255, 15, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de creer la couleur pour le rendu") ;

	SDL_Rect rectangle;
	rectangle.x = 300;
	rectangle.y = 300;
	rectangle.w = 200;
	rectangle.h = 120;

	if(SDL_RenderFillRect(renderer, &rectangle) !=0)
		SDL_ExitWithError("Impossible de dessiner un rectangle") ;

	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de creer la couleur pour le rendu") ;
	


	SDL_RenderPresent(renderer);
	SDL_Delay(5000);



	SDL_Delay(1000);
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


