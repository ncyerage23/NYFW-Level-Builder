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
	
	NYFW_Rect tile_rects[256];	// rects for each potential tile

	NYFW_Canvas tiles;		// the tiles to copy over
	NYFW_Rect tile_src_rects[256];	// rects for copying tiles

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
	
	/* ----- TILE RECTS ----- */
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			lmod.tile_rects[j * 16 + i] = (NYFW_Rect){ rx + i * tile_size, ry + j * tile_size, tile_size, tile_size };
	
	/* ----- TILE SOURCE RECTS ----- */
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			lmod.tile_src_rects[j * 16 + i] = (NYFW_Rect){ i * tile_size, j * tile_size, tile_size, tile_size };

	return 1;
}


void level_mod_draw()
{
	for (int i = 0; i < 2; i++)
		nyfw_canvasFill(lmod.scr, LBLUE, &lmod.border_rects[i]);
	
	nyfw_canvasBlit(lmod.tiles, NULL, lmod.scr, &lmod.level_rect);


	return;
	for (int i = 0; i < 256; i++) {
		int tile_idx = level.pixels[i];
		if (tile_idx == 0) continue;
			
		NYFW_Rect r = lmod.tile_src_rects[tile_idx];
		nyfw_canvasBlit(lmod.tiles, &r, lmod.scr, &lmod.tile_rects[i]); 
	}
}



void level_check_input(int x, int y)
{
	if (!IN_RECT(lmod.level_rect, x, y)) return;

	for (int i = 0; i < 256; i++) {
		if (IN_RECT(lmod.tile_rects[i], x, y)) {
			level.pixels[i] = current_tile;
			return;
		}
	}
}

void level_mod_shutdown()
{
	free(lmod.tiles.pixels);
}



