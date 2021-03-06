/**
 *
 * File: doms_stdlib.h
 *
 * Project: DoSH
 * Component: custom functions
 *
 * Authors: Dominic May;
 * 		   Lord_DeathMatch;
 *		   Mause
 *
 * Description: contains functions i required to build DoSH;
 *				it would be worth noting that not all these functions are used,
 *				or, for that matter, work (unfortunately, the compiler currently
 *				include all defined functions and code, no matter if they are
 *				actually used or not)
 *
**/

#ifndef __DOSH_DOMS_STDLIB_C
#define __DOSH_DOMS_STDLIB_C

#include "stdlib.h"
#include "doms_stdlib.h"
#include "ext/screen.h"
#include "string.h"

// return a C string with maximal length max_len
// adds a '\0' to the end of the string
// thus needs a buffer of size max_len+1 at least.
// also, prints from x,y onwards
void fgets(char* buf, int max_len, int x, int  y)
{
	int i; char c;
	for (i=0; i < max_len; i++) {
		c = doms_getch();
		if (c != '\n') {
			buf[i++] = c;
			eputc(c, x, y);
			x++;
		} else {
			break;
		}
	}
	buf[i] = '\0';
}


int doms_getch(){
	int ch;
	__asm {
		SET PUSH, A
		SET PUSH, B
		SET PUSH, C
		SET A, 1
		HWI [key_slot]
		SET <ch>, C
		SET C, POP
		SET B, POP
		SET A, POP
	}
	return ch;
}


/* returns true if val is special, false if not */
int if_special(int val) {
	int spec_keys[10] = {
		0x10,	// Backspace
		0x11,	// Return
		0x12,	// Insert
		0x13,	// Delete
//		0x20-0x7f	// ASCII in this range
		0x80,	// Arrow up
		0x81,	// Arrow down
		0x82,	// Arrow left
		0x83,	// Arrow right
		0x90,	// Shift
		0x91	// Control
	};
	int i;
	for (i=0; i<10; i++)
	{
		if (spec_keys[i] == val)
		{
			return true;  /* it was found */
		}
	}
	return false;  /* if it was not found */
}


// 32 columns by 12 rows
void cls() {
	eputs("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ", 0,0);
}


void asm_cls(){
	__asm {
		SET PUSH, A
		SET A, 0x8000
		:asm_cls_looper
			SET [A], 0x0
			ADD A, 1
			IFN A, 384
			SET PC, asm_cls_looper

		SET A, POP
	}
}


void anon_cls(){
	__asm{
		set b, [0x8000]
		set i, 0
		:clear_screen_loop
			set [b], 0x0000
			add b, 1
		    add i, 1
		    ifl i, 0x180
		    	set pc, clear_screen_loop
	}
}

void atlas_cls(){
	__asm{
		;// Clears the screen and sets the cursor to the first line (working)
		:clear
			SET PUSH, A
			SET PUSH, B
			SET PUSH, C

			SET A, 0x8000
			SET B, [video_clear]
			SET C, [video_width]
			MUL C, [video_height]
			ADD C, [video_mem]

		:clear_loop
			  SET [A], B
			  SET [1+A], B
			  SET [2+A], B
			  SET [3+A], B
			  ADD A, 4

			  IFN A, C
				  SET PC, clear_loop

		:video_mem
		dat 0xF800
		:video_font
		dat 0x0000
		:video_palette
		dat 0x0000
		:video_col
		dat 0x7000
		:video_cur
		dat 0x0000
		:video_clear
		dat 0x7020
		:video_width
		dat 0x0020
		:video_height
		dat 0x000C

		:clear_end
			  SET C, POP
			  SET B, POP
			  SET A, POP
	}
}


// int doms_scroll(char * lines) {
// 	int i;
// 	// int line = 0x8000;
// 	int x;
// 	int mem = 0x8000;
// 	for(i=0; i!=32-1; i++){

// 		for (x=0; x!=32; x++){
// 			lines[i] = *mem;
// 		}
// 		//mem
// 	}
// 	return 0;
// }


int atlas_scroll(){
	__asm {

	;// Scrolls the screen one line

	:scroll
		  SET PUSH, A
		  SET PUSH, X
		  SET PUSH, Y

		  SET X, [video_mem] ; Set X to the video memory
		  SET Y, [video_mem]
		  ADD Y, 0x0020 ; Set Y to the second line in the video memory

		  SET A, [video_width]
		  MUL A, [video_height]
		  ADD A, [video_mem]

	:scroll_loop1
		  SET [X], [Y]
		  SET [1+X], [1+Y]
		  SET [2+X], [2+Y]
		  SET [3+X], [3+Y]

		  ADD X, 4
		  ADD Y, 4

		  IFN Y, A
			SET PC, scroll_loop1

	:scroll_loop2
		  SET [X], [video_clear]
		  ADD X, 1
		  IFE X, A
			  SET PC, scroll_end
		  SET PC, scroll_loop2

	:scroll_end
		  SUB [video_cur], 0x20
		  SET Y, POP
		  SET X, POP
		  SET A, POP
		  SET PC, POP
	}
}


void scrn_border_colour(int color){
	__asm {
		SET PUSH, A
		SET PUSH, B
		SET A, 3
		SET B, <color>
		HWI [display_slot]
		SET B, POP
		SET A, POP
	}
}

// is this supposed to turn the cursor blink off?
int blink(int on_off){return 0;}


int loading_wheel(int x, int y, int times){
	// Displays 'spinning' wheel
	char segs[4] = {'|','/','-','\\'};
	int seg_point = 0;
	for (times; times!=0; times--){
		for (seg_point=0; seg_point!=3; seg_point++){
			eputc(segs[seg_point], x, y);
			// at the moment, does not use a delay
			// if it did, there would be one here :P
			// ie,
			// clock_delay(1);
		}
	}
	eputc(' ', x, y);
	return 0;
}


void doms_type(char* msg, int x, int y, int delay)
{
	int i = 0;
	int counter = 0;
	for (i = 0; *(msg + i) != '\0'; i++){
		//scrn_setc((*(msg + i) + 0xE000), x+i, 0);
		//scrn_setc((*(msg + i) + 0xE000), x+i, y);
		//doms_delay(delay);
		//scrn_setc((*(msg + counter) + 0xE000), x+counter, y);
		eputc((*(msg + counter) + 0xE000), x+counter, y);
		counter=counter+1;
		//printf(msg, 0,counter);
		doms_delay(delay);
	}
}


// this function is unreliable, do not use it
// if the the clock_delay function works, use that instead (it doesn't)
void doms_delay(int delay) {
	while (delay!=0){
		delay--;
	}
}


// int doms_compare(char * sone, char * stwo){
// 	int i;
// 	for (i=0;sone[i] != '\0'; i++){
// 		if (strcmp(sone[i], stwo[i]) == 1){
// 			return false;
// 		}
// 	}
// 	return true;
// }


// this bugs out atm, no real idea why
int clock_delay (int delay, int slot) { // delay in seconds
	__asm{
		SET PUSH, A
		SET PUSH, B
		SET PUSH, C
		SET A, 0x0
		SET B, 0x0
		SET C, 0x0
		:clockloopA				;// Part 1 of the loop, sets and resets the clock ticking.
			SET A, 0			;// Sets a to 0, which means when we interrupt our clock we set it to start ticking
			SET B, 1			;// Replace 60 with any integer to define how often the clock will tick. If you set it to 1, the clock will tick at a rate of 60/1 or 60 ticks per second. If it is 2 it will tick at 60/2, or 30 ticks per second, which is less presice. If it is 3 it is 60/3 or 20 TPS(Ticks per second) etc. Setting it to 60 means 1 tick = 1 second.
			HWI <slot>		;// Sends an interrupt to our clock. Replace (clock slot) with the actual clock slot. (But dont hard code it for portability)
								;// our clock should now be ticking at a rate of 1 TPS(Ticks per second)

		:clockloopB				;// Part 2 of the loop, which waits for ten seconds then does some code, then goes back to clockloopA. Runs directly after part 1.
			SET A, 1			;// sets a to one so we can get the amount of time since we last sent a 0 interrupt (an interrupt sent to the clock while a=0)
			HWI <slot>
			IFG C, <delay>			;//if C is 10 (or higher, because we might miss the exact tick where C = 10 and be stuck in an infinite loop)
				set pc, enddelay
			set pc, clockloopB	;//otherwise we loop

		:enddelay
		SET A, 0x0
		SET B, 0x0
		SET C, 0x0
		HWI <slot>
		;//set z, 777				;do whatever you want here instead of setting Z to 777
		;//set pc, clockloopA		;We set it to A because it resets the timer, and C only reads from the clocks last 0 interrupt.
		SET C, POP
		SET B, POP
		SET A, POP
	}
	return 0;
}


int blink_cursor(int times, int x, int y, int delay) { // this is untested
	while (times!=0) {
		eputc('|', x, y);
		doms_delay(delay);
		eputc(' ', x, y);
		doms_delay(delay);
		times = times - 1;
	}
	return 0;
}


void find_hw(session *current_session){ // initiates hardware, returns number of connected devices
	int hwcount;
	int clock_slot;

	__asm{
		SET PUSH, A
		SET PUSH, B
		SET PUSH, C
		SET PUSH, X
		SET PUSH, Y
		SET PUSH, Z
		SET PUSH, I
		SET PUSH, J
		HWN J
		SET <hwcount>, J
		:detect_hardware
			HWQ I
			IFE 0x7349, B
				IFE 0xf615, A
					SET [display_slot], I
			IFE 0x30cf, B
				IFE 0x7406, A
					SET [key_slot], I
			IFE 0x12d0, B
				IFE 0xb402, A
					SET <clock_slot>, I
			IFE 0x5678, B
				IFE 0x1234, A
					SET [floppy_slot], I
			ADD I, 1
			IFE I, J
				SET pc, end_find_hw
			SET pc, detect_hardware


		;// this next section is an attempt at
		;// mid-code variables :D
		set pc, variables_end
		:key_slot dat 0x0
		:display_slot
		;// :clock_slot dat 0x0
		:floppy_slot dat 0x0
		:fore_color dat 0xf ;0x0 .. 0xf
		:back_color dat 0x1 ;0x0 .. 0xf
		:carot_char dat 0x5f
		;// .EXPORT clock_slot
		.EXPORT floppy_slot
		.EXPORT fore_color
		.EXPORT back_color
		.EXPORT carot_char
		:variables_end

		:end_find_hw

		SET J, POP
		SET I, POP
		SET Z, POP
		SET Y, POP
		SET X, POP
		SET C, POP
		SET B, POP
		SET A, POP
	}
	current_session->hardware.clock.slot = 7777;
 	current_session->hardware.hwcount = hwcount;
 	// return current_session;
}

void rotate_by_one(char * arr[], int n){
   int i;
   for (i = n - 1;i > 0;i--){
      arr[i] = arr[i - 1];
   }
}

// int indexOf(char * arr[], char * string){
// 	unsigned int i;
// 	unsigned int numElements = sizeof(arr) / sizeof(arr[0]);

// 	for(i=0; i<numElements; ++i) {
// 	    if (strcmp(arr[i], string) == 0) {
// 	        return i;
// 	    }
// 	}

// 	if (i >= numElements) {
// 	    return -1;
// 	}
// }


#endif
