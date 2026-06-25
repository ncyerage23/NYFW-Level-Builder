/*
 * TILE PALETTE 
 *
 * Basically the same, but different.  
 *
 */

#include "level_builder.h"
#include <stdlib.h>

int current_tile = 1;

int blen = 10;
int tilep_size = 56; 


typedef struct {
	NYFW_Rect palette_rect;		// the whole module
	NYFW_Rect border_rects[4];

	NYFW_Canvas tiles;		// all the tiles
	NYFW_Rect tile_rects[16];

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
	
	/* ----- TILE RECTS ----- */
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			pmod.tile_rects[j*4+i] = (NYFW_Rect){ rx + i*tilep_size, ry + j*tilep_size, tilep_size, tilep_size };

	return 1;
}


void palette_mod_draw()
{
	for (int i = 0; i < 4; i++)
		nyfw_canvasFill(pmod.scr, LGREEN, &pmod.border_rects[i]);

	nyfw_canvasBlit(pmod.tiles, NULL, pmod.scr, &pmod.palette_rect);

	// highlight current tile
	NYFW_Rect r = pmod.tile_rects[current_tile];
	
	for (int i = r.x; i < r.x + r.w; i++) {
		nyfw_canvSetPixel(pmod.scr, i, r.y, 0);
		nyfw_canvSetPixel(pmod.scr, i, r.y+r.h-1, 0);
	}

	for (int j = r.y+1; j < r.y+r.h-1; j++) {
		nyfw_canvSetPixel(pmod.scr, r.x, j, 0);
		nyfw_canvSetPixel(pmod.scr, r.x+r.w-1, j, 0);
	}

}


void palette_check_input(int x, int y)
{
	if (!IN_RECT(pmod.palette_rect, x, y)) return;

	for (int i = 0; i < 16; i++) {
		if (IN_RECT(pmod.tile_rects[i], x, y)) {
			current_tile = i;
			break;
		}
	}
}


void palette_mod_shutdown()
{
	free(pmod.tiles.pixels);
}







