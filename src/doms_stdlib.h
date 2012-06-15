/**
 *
 * File: doms_stdlib.h
 *
 * Project: DoSH
 * Component: doms stdlib header
 *
 * Authors: Dominic May;
 *			Lord_DeathMatch;
 *			Mause
 *
 * Description: Header file for doms stdlib
 *
**/

#ifndef __DOSH_DEFINES_H
#define __DOSH_DEFINES_H

#include "doms_stdlib.c"

// prototypes to be defined :)
void init_screen();
void init_kb();
int doms_getch();
int if_special(int val);
void cls();
void asm_cls();
void atlas_cls();
int doms_scroll(char * lines);
void scrn_border_colour(int color);
int blink(int on_off);
int loading_wheel(int x, int y, int times);
void doms_type(char *msg, int x, int y, int delay);
void doms_delay(int delay);
int doms_compare(char * sone, char * stwo);
int clock_delay(int delay);
int blink_cursor(int times, int x, int y, int delay);
int find_hw();

#endif