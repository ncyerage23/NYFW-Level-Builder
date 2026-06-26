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
		strcat(filename, "default.nymap");
		strcat(file_path, "gallery/");
		strcat(file_path, filename);

		uint16_t* pixels = malloc(512);
		memset(pixels, 0, 512);
		level = nyfw_canvas(pixels, 16, 16, 16);
		return 1;
	}
	
	strcat(filename, arg);
	strcat(file_path, "gallery/");

	const char* ext = strrchr(filename, '.');
	if (ext != NULL && strcmp(ext, ".nymap") != 0) {
		printf("error: incorrect file extension\n");
		return 0;
	}
	else if (ext == NULL) {
		strcat(filename, ".nymap");
	}

	strcat(file_path, filename);

	if (!nyfw_loadNYMG(&level, file_path)) {
		uint16_t* pixels = malloc(512);
		memset(pixels, 0, 512);
		level = nyfw_canvas(pixels, 16, 16, 16);
	}

	return 1;
}


void free_tile()
{
	free(level.pixels);
}


void save_file()
{
	nyfw_saveNYMG(level, file_path);
	free_tile();
}



