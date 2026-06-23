/*
 * TILE LOADER
 *
 * reads a file (I already forget the name) and loads the tiles onto a single canvas, then returns
 * it. The main file will scale it up (two separate times) for the tile palette and level module. 
 *
 */

#include "level_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


NYFW_Canvas load_tiles()
{
	FILE* fp;
	fp = fopen("assets/tile_list.txt", "r");
	char line[256];

	uint16_t* pixels = malloc(2 * 32 * 32);
	NYFW_Canvas out = nyfw_canvas(pixels, 32, 32, 32);


	int count = 0;
	if (fp != NULL) {
		while(fgets(line, sizeof(line), fp) && count < 16) {
			line[strcspn(line, "\n")] = '\0';

			NYFW_Canvas tile;
			nyfw_loadNYMG(&tile, line);
		
			NYFW_Rect tile_rect = { 8 * (count % 4), 8 * (count / 4), 8, 8 };
			nyfw_canvasBlit(tile, NULL, out, &tile_rect);	
			
			free(tile.pixels);
			count++;
		}

		fclose(fp);
	}
	

	return out;
}


