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

#ifndef __DOSH_DOMS_STDLIB_H
#define __DOSH_DOMS_STDLIB_H

#include "doms_stdlib.c"
#include "defines.h"

// prototypes to be defined :)
void clear_cmd_bffr (char *read_in_command, int command_pointer);
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
// void rightRotatebyOne(int arr, int n);
// char *substring(char *src, size_t start, size_t size);
#endif