/*
 * LEVEL BUILDER!
 *
 * A little app for building maps/rooms for my platformer game. 
 * The maps will be stationary for right now, so this will be pretty durn simple. 
 *
 * Basically, it's just the other tile painter program, but instead of colors, 
 * I'll use tiles (drawn in the tile painter). So yeah. Pretty cool. 
 *
 * (for now) The maps will be stored as canvases, but the pixel data will actually be
 * tile data. I'm gonna use a ".nymap" file extension for the saved maps. Yup. 
 *
 */

#include "level_builder.h"
#include <unistd.h>
#include <stdlib.h>


NYFW_Canvas tile;
NYFW_Canvas scr;


/* ----- INIT/CLOSE ----- */
int setup(const char* arg)
{
	if (!nyfw_windowInit())
		return 0;
	
	scr = nyfw_getWindowCanvas();
	NYFW_Canvas tile_palette = load_tiles();

	if (!level_mod_init(scr, nyfw_canvasScaleUp(tile_palette, 10))) {
		free(tile_palette.pixels);
		nyfw_windowClose();
		return 0;
	}

	if (!palette_mod_init(scr, nyfw_canvasScaleUp(tile_palette, 7))) {
		free(tile_palette.pixels);
		level_mod_shutdown();
		nyfw_windowClose();
		return 0;
	}


	free(tile_palette.pixels);
	return 1;

}

void shutdown()
{
	level_mod_shutdown();
	palette_mod_shutdown();
	nyfw_windowClose();
}




/* ----- MAIN ----- */

// mouse
int mx = 10, my = 10;
float m_sensitivity_y = 1.5;
float m_sensitivity_x = 2.0;

void undraw_mouse()
{
	nyfw_canvSetPixel(scr, mx, my, 0);
	nyfw_canvSetPixel(scr, mx-1, my, 0);
	nyfw_canvSetPixel(scr, mx+1, my, 0);
	nyfw_canvSetPixel(scr, mx, my-1, 0);
	nyfw_canvSetPixel(scr, mx, my+1, 0);

}


void draw_mouse()
{
	nyfw_canvSetPixel(scr, mx, my, 0xffff);
	nyfw_canvSetPixel(scr, mx-1, my, 0xffff);
	nyfw_canvSetPixel(scr, mx+1, my, 0xffff);
	nyfw_canvSetPixel(scr, mx, my-1, 0xffff);
	nyfw_canvSetPixel(scr, mx, my+1, 0xffff);

}


int main(int argc, char* argv[]) 
{
	
	if (!setup("")) return 1;

	
	nyfw_canvasClear(scr);
	level_mod_draw();
	palette_mod_draw();
	nyfw_windowPresent();
	

	sleep(3);

	shutdown();
	return 0;
}




