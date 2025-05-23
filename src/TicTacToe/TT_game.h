#include <stdlib.h>
#include <stdint.h>
//FIX: what integer type should this be?
typedef uint16_t u16;

typedef struct TT_Pattern TT_Pattern;

struct TT_Pattern {
	u16 (*coords)[2]; //[0]=x, [1]=y
	size_t num_elems;
};
typedef struct TT_BoardFinite TT_BoardFinite;
struct TT_BoardFinite {
	u16 sz_board;
	u16 data[]; //square 2d array
};
typedef struct TT_Game TT_Game;
struct TT_Game {
	TT_BoardFinite *board;
	TT_Pattern *winning_patterns;
	u16 num_winning_patterns;
	/*TODO: support for variable players(if necessary)*/
	char const* *players; /*array of pointers to string literals.*/
	u16 num_players;

	int (*place_piece)(TT_Game const* this, u16 player, u16 x, u16 y);
};


TT_Game* TT_CreateGame();
void TT_DestroyGame(TT_Game *game);
