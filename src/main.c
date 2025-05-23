#include <stdio.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "TicTacToe/TT_game.h"

static SDL_Window *window;
static SDL_Renderer *renderer;

#define WINDOW_WIDTH 648
#define WINDOW_HEIGHT 480

typedef struct State State;
struct State {
	TT_Game *game;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	//SDL initializers
	SDL_SetAppMetadata("tictac", "1.0", NULL);
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH,WINDOW_HEIGHT, 0, &window, &renderer)) {
		SDL_Log("couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	//My initializers

	*appstate = malloc(sizeof(State));
	State *state = (State*)(*appstate);
	state->game = TT_CreateGame();

	return SDL_APP_CONTINUE;

}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

	TT_Game *game = ((State*)appstate)->game;
	float mx,my;
	static int player = 1;
	switch(event->type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			SDL_GetMouseState(&mx, &my);
			int x = game->board->sz_board*mx/(480);
			int y = game->board->sz_board*my/(480);
			printf("sz:%d\n",game->board->sz_board );
			printf("x:%d\n", x);
			printf("y:%d\n", y);
			int status = game->place_piece(game,player,x,y);
			if(!status) player = (player == 1)? 2 : 1;
			if(status >= 1) {
				TT_DestroyGame(game);
				((State*)appstate)->game = TT_CreateGame();
			}
			break;
		case SDL_EVENT_QUIT: return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppIterate(void *appstate) {
	SDL_SetRenderDrawColor(renderer, 0, 0,0,255);
	SDL_RenderClear(renderer);
	TT_Game *game = ((State*)appstate)->game;
	u16 const sz_board = game->board->sz_board;
	u16 const*const data = game->board->data;
	size_t const len_side = 480;
	size_t const len_tile = len_side/sz_board;
	size_t const margin = 3;

	printf("bsz:%hu\n", sz_board);
	int colormap[][3] = {[0]={100,100,100}, [1]={255,0,0}, [2]={0,0,255}};
	for(size_t i = 0; i < sz_board; ++i) {
		for(size_t j = 0; j < sz_board; ++j) {
			SDL_FRect cursquare = {.x=j*len_tile,.y=i*len_tile,.h=len_tile-margin,.w=len_tile-margin};
			printf("accessed:%hu\n", data[i*sz_board+j]);
			SDL_SetRenderDrawColor(renderer, colormap[data[i*sz_board+j]][0], colormap[data[i*sz_board+j]][1], colormap[data[i*sz_board+ j]][2], 255);
			SDL_RenderFillRect(renderer, &cursquare);
		}
	}
	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
}
