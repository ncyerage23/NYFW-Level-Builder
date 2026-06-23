/*
 * LEVEL BUILDER
 *
 * A program for painting little 8x8 tiles for games. Saved to my .nymg format. 
 * Idk what else to put here, but yeah. This is the header file. 
 *
 */

#ifndef LEVEL_BUILDER_H
#define LEVEL_BUILDER_H

#include "NYFW/nyfw.h"
#include <stdio.h>

#define IN_RECT(r, x, y)	((r).x <= (x) && (r).y <= (y) && (x) < (r).x + (r).w && (y) < (r).y + (r).h) ? 1 : 0


/* ----- GLOBALS ----- */
extern NYFW_Canvas tile;
extern char file_path[256];
extern uint16_t current_color;


/* ----- LEVEL MODULE ----- */
int level_mod_init(NYFW_Canvas scr, NYFW_Canvas tiles);
void level_mod_draw();
void level_check_input(int x, int y);
void level_mod_shutdown();


/* ----- FILE MODULE ----- */
int init_file(const char* arg);
void save_file();
void free_tile();


/* ----- PALETTE MODULE ----- */
int palette_mod_init(NYFW_Canvas scr, NYFW_Canvas tiles);
void palette_mod_draw();
void palette_check_input(int x, int y);
void palette_mod_shutdown();


/* ----- TILE LOADER ----- */
NYFW_Canvas load_tiles();


#endif
