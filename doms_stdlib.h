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
 *				or, for that matter, work
 *
**/



#include "include\ext\screen.h"

//void (*func)(char* msg, int x, int y) = &scrn_sets;
/*
void printf(char* msg, int x, int y)
{
	int i = 0;
	for (i = 0; * (msg + i) != '\0'; i += 1)
		eputc((*(msg + i) + 0xE000), x + i, y);
	//	scrn_setc((*(msg + i) + 0xE000), x + i, y);
}
*/


void init_screen() {
	__asm{
		SET A, 0
		SET B, 0x8000
		HWI [display_int]
		;HWI 0
	}
}


int init_kb(){
	__asm {
		SET PUSH, A
		SET A, 0
		HWI [key_int]
		SET A, POP
	}
	return 0;
}


int doms_getch(){
	int ch;
	__asm {
		SET PUSH, A
		SET PUSH, B
		SET PUSH, C
		SET A, 1
		HWI 1
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
	    return 0;  /* it was found */
	 }
   }
   return -1;  /* if it was not found */
}


// 32 columns by 12 rows
int cls() {
	int i;
	//eputs("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ", 0,0);
	for (i = 12; i != 0; i--) {
		eputs("                                ", i, 0);
	}
}


int asm_cls(){
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


int scrn_border_colour(int color){
	__asm {
		SET PUSH, A
		SET PUSH, B
		SET A, 3
		SET B, <color>
		HWI [display_int]
		SET B, POP
		SET A, POP
	}
	return 0;
}


int blink_on(){}


int loading_wheel(int x, int y, int times){ // only performs one iterations :P
	// Displays 'spinning' wheel
	char segs[4] = {'|','/','-','\\'};
	int seg_point = 0;
	while (times!=0){
		// sing us a song tonight?
		for (seg_point=0; seg_point!=3; seg_point++){
			eputc(segs[seg_point], x, y);
			// at the moment, does not use a delay
			// if it did, there would be one here :P
			// ie,
			// clock_delay(1);
		}
		times--;
	}
	eputc(' ', x, y);
	return 0;
}


int doms_type(char* msg, int x, int y, int delay)
{
	int i = 0;
    int counter = 0;
	for (i = 0; *(msg + i) != '\0'; i++)
		//scrn_setc((*(msg + i) + 0xE000), x+i, 0);
        //scrn_setc((*(msg + i) + 0xE000), x+i, y);
        //doms_delay(delay);
        //scrn_setc((*(msg + counter) + 0xE000), x+counter, y);
		eputc((*(msg + counter) + 0xE000), x+counter, y);
        counter=counter+1;
        //printf(msg, 0,counter);
        doms_delay(delay);
}


int doms_delay(int delay) {
    while (delay!=0)
		delay--;
    return 0;
}


int doms_compare(char * sone, char * stwo){
	// this is a placeholder for the moment :)
	int i;
	for (i=0;sone[i] != '\0'; i++){
		if (strcmp(sone[i], stwo[i]) == 1){
			return false;
		}
	}
	return true;
}


int clock_delay (int delay) { // delay in seconds
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
			HWI [clock_int]		;// Sends an interrupt to our clock. Replace (clock slot) with the actual clock slot. (But dont hard code it for portability)
								;// our clock should now be ticking at a rate of 1 TPS(Ticks per second)

		:clockloopB				;// Part 2 of the loop, which waits for ten seconds then does some code, then goes back to clockloopA. Runs directly after part 1.
			SET A, 1			;// sets a to one so we can get the amount of time since we last sent a 0 interrupt (an interrupt sent to the clock while a=0)
			HWI [clock_int]
			IFG C, <delay>			;//if C is 10 (or higher, because we might miss the exact tick where C = 10 and be stuck in an infinite loop.) we do :somecode
				set pc, enddelay
			set pc, clockloopB	;//otherwise we loop
    
		:enddelay
		SET A, 0
		SET B, 0
		HWI [clock_int]
		;//set z, 777				;do whatever you want here instead of setting Z to 777
		;//set pc, clockloopA		;We set it to A because it resets the timer, and C only reads from the clocks last 0 interrupt.
		SET C, POP
		SET B, POP
		SET A, POP		
	}
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


int find_hw(){ // initiates hardware, returns number of connected devices
	int hwcount;
	char *tmp;
	__asm{
		SET PUSH, A
		SET PUSH, B
		SET PUSH, Z
		SET PUSH, J
		SET PUSH, I
		HWN J
		SET <hwcount>, J
		:detect_hardware
			HWQ I
			IFE 0x7349, B
				IFE 0xf615, A
					SET [display_int], I
			IFE 0x30cf, B
				IFE 0x7406, A
					SET [key_int], I
			IFE 0x12d0, B
				IFE 0xb402, A
					SET [clock_int], I
			ADD I, 1
			IFE I, J
				SET pc, end_find_hw
			SET pc, detect_hardware    


        ;// this next section is an attempt at
        ;// mid-code variables :D
        set pc, variables_end
        :key_int dat 0x0
        :display_int
		:clock_int dat 0x0
        :fore_color dat 0xf ;0x0 .. 0xf
        :back_color dat 0x1 ;0x0 .. 0xf
        :carot_char dat 0x5f      
        :variables_end
        
        :end_find_hw

		SET I, POP
		SET J, POP
		SET Z, POP
		SET B, POP
		SET A, POP
	}
	return hwcount;
}


void scrn_setc_green(char chr, int x)
{
	int mem = 0x8000 + x;
	*mem = (chr + 0xA000);
}


void print_number(char number, char scrn_addr)
{
    char length = 0;
    char tmp = number;
    while(tmp > 0)
    {
        length++;
        tmp /= 10;
    }
    scrn_addr += length;
    char digit;
    while(number > 0)
    {
        digit = number % 10;
        number /= 10;

        *(scrn_addr) = digit + 48 + 0xC000;
        scrn_addr--;
    }
}
