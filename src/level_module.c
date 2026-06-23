/*
 * LEVEL MODULE
 *
 * The place the user will build the level! Very simple stuff. 
 * I mean, I'm really just copying old code and changing it. So yeah. 
 *
 */

#include "level_builder.h"
#include <stdlib.h>


int border_len = 20;	// length of LevelModule border
int tile_size = 80;

typedef struct {
	NYFW_Rect level_rect;		// rect for the entire level
	NYFW_Rect border_rects[2];	// rects for drawing the border
	
	NYFW_Canvas tiles;		// the tiles to copy over

	NYFW_Canvas scr;
} LevelModule;

LevelModule lmod;


int level_mod_init(NYFW_Canvas scr, NYFW_Canvas tiles)
{
	lmod.scr = scr;
	lmod.tiles = tiles;

	/* ----- SCREEN DIMENSIONS ----- */
	int sw = scr.width, 	sh = scr.height;		// screen dimensions
	int centerx = sw / 2, 	centery = sh / 2;		// center of the screen
	
	/* ----- MODULE RECT ----- */
	int rx = centerx - centery,	ry = 0;
	int rl = sh;
	lmod.level_rect = (NYFW_Rect){ rx, ry, rl, rl };

	/* ----- BORDER RECTS ----- */
	lmod.border_rects[0] = (NYFW_Rect){ rx-border_len, ry, border_len, rl };	// left
	lmod.border_rects[1] = (NYFW_Rect){ rx+rl, ry, border_len, rl };		// right
	
	
	return 1;
}


void level_mod_draw()
{
	for (int i = 0; i < 2; i++)
		nyfw_canvasFill(lmod.scr, LBLUE, &lmod.border_rects[i]);

}



void level_check_input(int x, int y)
{

}

void level_mod_shutdown()
{
	free(lmod.tiles.pixels);
}
