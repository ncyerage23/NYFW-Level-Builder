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


	if (!nyfw_inputInit(INPUT_MOUSE | INPUT_KEYS)) { 
		free_tile();
		nyfw_windowClose();
		return 0; 
	}

	if (!tile_mod_init(scr)) {
		free_tile();
		nyfw_inputClose();
		nyfw_windowClose();
		return 0;
	}

	if (!palette_mod_init(scr)) {
		free_tile();
		nyfw_inputClose();
		nyfw_windowClose();
		return 0;
	}
}

void shutdown()
{
	save_file();
	nyfw_inputClose();
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
	NYFW_Canvas tile_palette = load_tiles();
	
	if (!nyfw_windowInit())
		return 0;
	scr = nyfw_getWindowCanvas();
	
	nyfw_canvasClear(scr);
	
	NYFW_Canvas test = nyfw_canvasScaleUp(tile_palette, 10);

	nyfw_canvasBlit(test, NULL, scr, NULL);




	nyfw_windowPresent();
	sleep(1);

	free(tile_palette.pixels);
	free(test.pixels);
	nyfw_windowClose();
	


	return 0;






	const char* arg;
	if (argc <= 1) arg = "";
	else arg = argv[1];

	if( !setup(arg) ) return 1;
	
	int sw = scr.width, sh = scr.height;
	nyfw_canvasClear(scr);

	while (1) {
		nyfw_inputPoll();
		
		// update (TODO: make this a separate function)
		if (nyfw_inputKeyPressed(NYFW_KEY_ESC)) break;

		int mdx = (float)nyfw_inputMouseDX() * m_sensitivity_x;
		int mdy = (float)nyfw_inputMouseDY() * m_sensitivity_y;

		if (nyfw_inputMBPressed(NYFW_MB_L)) {
			tile_check_input(mx+mdx, my+mdy);
			palette_check_input(mx+mdx, my+mdy);
		}

		// draw (TODO: make this also a separate function)
		undraw_mouse();
		tile_mod_draw();
		palette_mod_draw();
		mx += mdx;
		my += mdy;
		draw_mouse();

		// present
		nyfw_windowPresent();
	}


	shutdown();
	return 0;
}




