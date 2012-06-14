/**
 *
 *	File:		dosh.c
 *
 *	Project:	DoSH v.10
 *	Component:	Point insertion
 *
 *	Authors:	Dominic May;
 *				Lord_DeathMatch;			
 *				Mause
 *
 *	Description:	DoSH = Doms Own SHell
 *
 **/

#include "../include/stdlib.h"
#include "../include/ext/screen.h"
#include "../include/string.h"
#include "defines.h"
#include "doms_stdlib.h"
#include "builtins.c"


// TODO: implement scrolling :P
// 		will most likely either require a buffer (array?)
//		to store the information whilst it scrolls
// 		will probably implement a function for this :)


// TODO: implement previous commands; rather than writing the read_in_command to NULL :P
// REM_COMMAND will store the constant that defines how many to remember


int main() {
	// define variables :)
	int hwcount;
	int ch; 					// contains the most recent character entered into the keyboard
	int ch_stat;				// contains boolean indicating whether or not the current ch is special
	int breaker = false;

	struct command_return_struct *command_info;

	char read_in_command[COMMAND_LENGTH];
	int command_pointer = 0;
	
/*	char * previous_commands[REM_COMMAND];
	int previous_command_pointer = 0;
*/
	// line buffer :)
	char * lines[16];

	// points to where the cursor is
	int x=0;
	int y=0;

	scrn_border_colour(0);

	eputs("Loading", 0, 0);		// Display loading screen
	
	//hwcount = find_hw(); // currently does not work, not sure why
	init_screen(); 		// initialize screen to 0x8000
	scrn_border_colour(0);
	eputc('.', 8, 0);	// Display second point of loading screen
	init_kb();	   		// init keyboard :)
	eputc('.', 9, 0);	// Display third point of loading screen

	//atlas_cls(); // clear code stolen (sorry) from the AtlasOS O.S.
    cls(); // clear screen
    //asm_cls(); // assembly based screen cleaner; supposed to be much faster
    // i think it is bugging out a bit though
	eputs("DoSH version 1.0", x, y);  	// display DoSH version

	x=3;
	y=1;
	//clock_delay(1, clock_int);	// clock delay, does not work

	eputs(">> ", 0, 1);	

	while (breaker!=true){ 									// primary application loop
		ch=0;										// reset ch
		ch = doms_getch();   						// get a character in the form of an int from the keyboard
		ch_stat = if_special(ch);					// see if it a special key
		while (ch!=0){								// while ch is not 0
			if (ch_stat!=0){						// if is not a special key, print it to the terminal
				eputc(ch, x, y);					// print the ch to the terminal
				if (strlen(read_in_command)<COMMAND_LENGTH-1){
					//append(read_in_command, ch); 	// append the ch the the current command
					read_in_command[command_pointer] = ch;
					command_pointer++;
				}
				x++;								// increment the cursor position
			} else if (strcmp(ch_stat, 0) == 0) {	// if ch was a special key
				if (strcmp(ch, BACKSPACE) == 0) {	// if the special key was a backspace  specpnt("backspace")
					if (x > 3){						// if the cursor is not inside the prompt
						x--;						// decrement the cursor position
						command_pointer--;
						read_in_command[command_pointer] = '\0'; // remove the last character from the current command
						eputc(' ', x, y);			// clear spot the screen					
					}
				} else if (strcmp(ch,RETURN)==0) {	// if the special key was a return specpnt("return"))
					if (true){//(strcmp(read_in_command[1],'\0')!=0){
						y++;							// increment the cursor-y position, standard :P
						x=0;
						//if (strcmp(read_in_command, "exit") == 0){ // this is technically a built-in, but it is easy to implement here :P
						if (!true){
							x=0;
							y=0;
							breaker = true;			// this doesn't seem to work at the moment, i need to work out why
							break;					// i will probably just write a function to compare them myself :P
						} else {
							eputs(read_in_command, x, y); y++;
		/*					command_info = interpret_command(read_in_command, x, y);
							y+=command_info.y_moved;
		*/					x=3;					// move the cursor to the home position
							while ((command_pointer)!=0){						// this will tidy up the command buffer ^^
								read_in_command[command_pointer] = '\0';
								command_pointer--;
							}
							read_in_command[0] = '\0';
							eputs(">> ", 0, y);					
						}
					} else {
						y++;
						x=3;
						eputs(">> ", 0, y);
					}
				} else if (strcmp(ch, ARROW_LEFT)) {
					if (x > 3){	x--; }				// decrement the cursor position
				} else if (strcmp(ch, ARROW_RIGHT)) {
					if (x > 3){ x++; }				// increment the cursor position
				} else {
					eputc('?', x, y);				// print the ch to the terminal
					x++;							// increment the cursor position
				}
			}
			ch=0;									// reset ch
		}
		
	}
	cls();
	eputs("SHUT. DOWN.", 0, 0);
	abort();
	return 0;
}


// all commands are assumed to return an array containing the number
// of lines on the y-axis the command took and the exit status
// command id that was executed :P (0 if no command was executed; ie, the command does not exist)
// and an exit message, if any
// struct command_return_struct * 
void interpret_command(char * read_command, int x, int y) {
	int y_moved=1; y++;
	struct command_return_struct crs;
	//int num_functions = (sizeof(functions)/sizeof *functions ));
	//int num_functions = functions[ sizeof array / sizeof *array - 1 ];
	//int i;
/*	for (i=0; functions[-1]!=functions[i]; i++) {
		if (strcmp(functions[sizeof functions / sizeof *functions-1].function_name, read_command) == 0){
			//functions[function];//(x,y);
		} else {
			crs.command_id = 0;
			crs.command_message = 'NOT_FOUND';
			crs.command_status = 1;
		}
	}	*/
	if (strcmp(read_command, "echo") == 0) {
		crs = echo(x,y);
/*		crs.y_moved = 2;
		crs.command_id = 1;
		crs.command_message = 'SUCCESS';
		crs.command_status = 0;
*/	} else {
		crs.y_moved = 0;
		crs.command_id = 0;
		crs.command_message = 'NOT_FOUND';
		crs.command_status = 1;
	}
	return crs; // return the various 
}


/*
Reference data; don't mind me!

int echo(int x, int y){}

struct command_return_struct {
	int y_moved;
	int command_status;
	int command_id;
	char * command_message;
};

*/