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

#include "defines.h"

// #include "doms_stdlib.c"

// prototypes to be defined :)
int doms_getch();
void fgets(char* buf, int max_len, int x, int y);
int if_special(int val);
void cls();
// void asm_cls();
// void anon_cls();
// void atlas_cls();
// int doms_scroll(char * lines);
// void scrn_border_colour(int color);
// int blink(int on_off);
// int loading_wheel(int x, int y, int times);
// void doms_type(char *msg, int x, int y, int delay);
void doms_delay(int delay);
// int doms_compare(char * sone, char * stwo);
int clock_delay(int delay, int slot);
// int blink_cursor(int times, int x, int y, int delay);
void find_hw(session *current_session);
void rotate_by_one(int arr, int n);
// char *substring(char *src, size_t start, size_t size);
int indexOf(char * arr[], char * string);
#endif
