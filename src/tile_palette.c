/*
 * TILE PALETTE 
 *
 * Basically the same, but different.  
 *
 */

#include "level_builder.h"
#include <stdlib.h>

uint16_t current_color = 0x0000;
int cur_col_idx = 0;

int blen = 10;
int tilep_size = 56; 


typedef struct {
	NYFW_Rect palette_rect;		// the whole module
	NYFW_Rect border_rects[4];

	NYFW_Canvas tiles;	// all the tiles
	
	NYFW_Canvas scr;		// maybe make this a global? Idk. 
} PaletteModule;

PaletteModule pmod;


int palette_mod_init(NYFW_Canvas scr, NYFW_Canvas tiles)
{
	pmod.scr = scr;
	pmod.tiles = tiles;
	
	/* ----- SCREEN DIMENSIONS ----- */
	int sw = scr.width,	sh = scr.height;
	int centerx = sw/2,	centery = sh/2;

	/* ----- PALETTE RECT ----- */
	int rl = tilep_size * 4;
	int rx = 48,	ry = 528;
	pmod.palette_rect = (NYFW_Rect){ rx, ry, rl, rl };

	/* ----- BORDER RECTS ----- */
	pmod.border_rects[0] = (NYFW_Rect){ rx-blen, ry-blen, rl+2*blen, blen };	// top
	pmod.border_rects[1] = (NYFW_Rect){ rx-blen, ry+rl, rl+2*blen, blen };		// bottom
	pmod.border_rects[2] = (NYFW_Rect){ rx-blen, ry, blen, rl };			// left
	pmod.border_rects[3] = (NYFW_Rect){ rx+rl, ry, blen, rl };			// right
		

	return 1;
}


void palette_mod_draw()
{
	for (int i = 0; i < 4; i++)
		nyfw_canvasFill(pmod.scr, LGREEN, &pmod.border_rects[i]);

	nyfw_canvasBlit(pmod.tiles, NULL, pmod.scr, &pmod.palette_rect);

}


void palette_check_input(int x, int y)
{

}


void palette_mod_shutdown()
{
	free(pmod.tiles.pixels);
}







