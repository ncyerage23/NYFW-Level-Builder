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
 *
 *
 * IMPORTANT!!!! DO NOT RUN THIS UNTIL YOU CHANGE A BUNCH OF STUFF!!!
 * I tried running it and it crashed immediately, so a lot is gonna need to 
 * change before I try again. Idk what yet, but a lot. 
 *
 */

#include "level_builder.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


NYFW_Canvas level;
NYFW_Canvas scr;


/* ----- INIT/CLOSE ----- */
int setup(const char* arg)
{
	if (!init_file(arg)) return 0;

	if (!nyfw_windowInit())
		return 0;
	
	scr = nyfw_getWindowCanvas();
	NYFW_Canvas tile_palette = load_tiles();

	if (!level_mod_init(scr, nyfw_canvasScaleUp(tile_palette, 8))) {
		free_tile();
		free(tile_palette.pixels);
		nyfw_windowClose();
		return 0;
	}

	if (!palette_mod_init(scr, nyfw_canvasScaleUp(tile_palette, 7))) {
		free_tile();
		free(tile_palette.pixels);
		level_mod_shutdown();
		nyfw_windowClose();
		return 0;
	}
	
	if (!nyfw_inputInit(INPUT_MOUSE | INPUT_KEYS)) {
		free_tile();
		free(tile_palette.pixels);
		level_mod_shutdown();
		palette_mod_shutdown();
		nyfw_windowClose();
		return 0;
	}

	free(tile_palette.pixels);
	return 1;

}

void shutdown()
{
	save_file();
	level_mod_shutdown();
	palette_mod_shutdown();
	nyfw_inputClose();
	nyfw_windowClose();
}



/* ----- MOUSE ----- */

int mx = 10, my = 10;
int mdx = 0, mdy = 0;
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


/* ----- UPDATE/DRAW ----- */
int running = 1;

void update()
{
	nyfw_inputPoll();

	if (nyfw_inputKeyPressed(NYFW_KEY_ESC)) 
	{
		running = 0;
		return;
	}

	mdx = (float)nyfw_inputMouseDX() * m_sensitivity_x;
	mdy = (float)nyfw_inputMouseDY() * m_sensitivity_y;

	if (nyfw_inputMBPressed(NYFW_MB_L)) {
		level_check_input(mx+mdx, my+mdy);
		palette_check_input(mx+mdx, my+mdy);
	}

}


void draw()
{
	undraw_mouse();
	level_mod_draw();
	palette_mod_draw();
	mx += mdx;
	my += mdy;
	draw_mouse();
}


/* ----- MAIN ----- */

int main(int argc, char* argv[]) 
{
	const char* arg;
	if (argc <= 1) arg = "";
	else arg = argv[1];

	if (!setup(arg)) return 1;	
	nyfw_canvasClear(scr);
	
	while (running) {
		update();
		if (!running) break;
		draw();
		nyfw_windowPresent();
	}

	shutdown();
	return 0;
}




