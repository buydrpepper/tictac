#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "TT_game.h"

int TT_PlacePieceFinite(TT_Game const*const this, u16 const player, u16 const x, u16 const y) {
	u16 const sz_board = this->board->sz_board;
	u16 *const data_ref = this->board->data;
	if(x >= sz_board || y >= sz_board) return -1;
	if(data_ref[y*sz_board+x]) return -1;
	data_ref[y*sz_board+x] = player;

	for(u16 i = 0 ; i < this->num_winning_patterns; ++i) {
		size_t const num_coords = this->winning_patterns[i].num_elems;
		u16 const (*coords_ref)[2] = this->winning_patterns[i].coords;
		for(size_t j = 0; j < num_coords; ++j) {
			u16 const offsx = coords_ref[j][0];
			u16 const offsy = coords_ref[j][1];
			int found = 1;
			for(size_t k = 0; k < num_coords; ++k) {
				u16 const dx = coords_ref[k][0];
				u16 const dy = coords_ref[k][1];

				int32_t x2 = x+dx-offsx;
				int32_t y2 = y+dy-offsy;
				if(x2 >= sz_board || y2 >= sz_board || x2 < 0 || y2 < 0 ||


					!printf("x2: %d\n",x2)||
					!printf("y2: %d\n",y2)||

					data_ref[y2*sz_board + x2] != player) {
					found = 0;
					break;
				}
			}
			if(found) return player;
		}
	}
	return 0;
}

TT_BoardFinite* TT_CreateBoardFinite(u16 const sz) {
	TT_BoardFinite *ret = calloc(sizeof(TT_BoardFinite) + sz*sz*sizeof(ret->data[0]),1);
	ret->sz_board = sz;
	return ret;
}
void TT_DestroyBoardFinite(TT_BoardFinite *board) {
	free(board);
}
TT_Game* TT_CreateGame() {
	//temp variables for debugging
	int const INIT_SIZE = 5;
	#define NUM_WINNING_PAT 4
	u16 const WINNING_PATS[NUM_WINNING_PAT][3][2] = {
		{{0,0},{1,0},{2,0}},
		{{0,0},{1,1},{2,2}},
		{{0,2},{1,1},{2,0}},
		{{0,0},{0,1},{0,2}}
	};



	TT_Game *const ret = calloc(1,sizeof(*ret));
	ret->board = TT_CreateBoardFinite(INIT_SIZE);

	//init winning patterns
	//NOTE: This part is really bad and i will replace it after debugging
	ret->num_winning_patterns = NUM_WINNING_PAT;
	ret->winning_patterns = malloc(NUM_WINNING_PAT*sizeof(*ret->winning_patterns));
	for(int a = 0; a < NUM_WINNING_PAT; ++a) {
		ret->winning_patterns[a].num_elems = 3;
		ret->winning_patterns[a].coords = malloc(3*sizeof(*ret->winning_patterns[0].coords));
		for(int i = 0; i < 3; ++i) {
			ret->winning_patterns[a].coords[i][0] = WINNING_PATS[a][i][0];
			ret->winning_patterns[a].coords[i][1] = WINNING_PATS[a][i][1];
		}
	}
	


	//init player
	ret->num_players = 2;
	ret->players = malloc(ret->num_players * sizeof(*ret->players));
	ret->players[0] = "player 1";
	ret->players[1] = "player 2";

	//init member functions
	ret->place_piece = TT_PlacePieceFinite;
	return ret;
}
void TT_DestroyGame(TT_Game *game) {
	for(size_t i = 0; i < game->num_winning_patterns; ++i) {
		free(game->winning_patterns[i].coords);
	}
	TT_DestroyBoardFinite(game->board);
	free(game->winning_patterns);
	free(game->players);
}
