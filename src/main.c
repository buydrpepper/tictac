#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window;
static SDL_Renderer *renderer;

#define WINDOW_WIDTH 648
#define WINDOW_HEIGHT 480

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	SDL_SetAppMetadata("tictac", "1.0", NULL);
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH,WINDOW_HEIGHT, 0, &window, &renderer)) {
		SDL_Log("couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;

}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	switch(event->type) {
		case SDL_EVENT_QUIT: return SDL_APP_SUCCESS;
		default: return SDL_APP_CONTINUE;
	}
}
SDL_AppResult SDL_AppIterate(void *appstate) {
	SDL_SetRenderDrawColor(renderer, 88, 88,88,255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
}
