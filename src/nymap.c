/* 
 * FILE READING FOR LEVEL BUILDER
 *
 *
 */


#include "level_builder.h"
#include <stdlib.h>
#include <string.h>

char file_path[256];
char filename[256];


int init_file(const char* arg)
{
	if (strlen(arg) == 0) {
		strcat(filename, "default.nymg");
		strcat(file_path, "gallery/");
		strcat(file_path, filename);

		uint16_t* pixels = malloc(128);
		tile = nyfw_canvas(pixels, 8, 8, 8);
		return 1;
	}
	
	strcat(filename, arg);
	strcat(file_path, "gallery/");
	
	const char* ext = strrchr(filename, '.');
	if (ext != NULL && strcmp(ext, ".nymg") != 0) {
		printf("error: incorrect file extension\n");
		return 0;
	}
	else if (ext == NULL) {
		strcat(filename, ".nymg");
	}

	strcat(file_path, filename);

	if (!nyfw_loadNYMG(&tile, file_path)) {
		uint16_t* pixels = malloc(128);
		tile = nyfw_canvas(pixels, 8, 8, 8);
	}

	return 1;
}


void free_tile()
{
	free(tile.pixels);
}


void save_file()
{
	nyfw_saveNYMG(tile, file_path);
	free_tile();
}



