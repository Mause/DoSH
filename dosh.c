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

struct command_return_struct {
	int y_moved;
	int command_status;
	int command_id;
	char * command_message;
};

/*
struct Command {
	char * function_name;
	struct command_return_struct function_pointer;
};
*/

int main() {

	eputs("Loading", 0, 0);		// Display loading screen
	
	//char 

	int hwcount;
	int ch; 					// will probably contain the most recent charactor entered into the keyboard
	int ch_stat;				// contains bool indicating whether or not the current char is special

	struct command_return_struct *command_info;

	char read_in_command[COMMAND_LENGTH];
	int command_pointer = 0;
	
	// points to where the cursor is
	int x=0;
	int y=0;
	eputc('.', 8, 0);	// Display first point of loading screen
	//hwcount = find_hw(); // currently does not work, not sure why
	init_screen(); 		// initialise screen to 0x8000
	scrn_border_colour(0);
	eputc('.', 9, 0);	// Display second point of loading screen
	init_kb();	   		// init keyboard :)
	eputc('.', 10, 0);	// Display third point of loading screen


    cls(); // clear screen
	eputs("DoSH version 1.0", x, y);  	// display DoSH version

	x=3;
	y=1;
	//clock_delay(1, clock_int);	// clock delay, does not work either

	eputs(">> ", 0, 1);	
//	loading_wheel(3, 1, 4);
	while (true){ 									// primary application loop
		ch=0;										// reset ch
		ch = doms_getch();   						// get a charactor in the form of an int from the keyboard
		ch_stat = if_special(ch);					// see if it a special key
		while (ch!=0){								// while ch is not 0
			if (ch_stat!=0){						// if is not a special key, print it to the terminal
				eputc(ch, x, y);					// print the ch to the terminal
				if (strlen(read_in_command)<COMMAND_LENGTH-1){
					append(read_in_command, ch); 	// append the ch the the current command
				}
				x++;								// increment the cursor position
			} else if (strcmp(ch_stat,0) == 0) {	// if ch was a special key
				if (strcmp(ch,BACKSPACE) == 0) {	// if the special key was a backspace  specpnt("backspace")
					if (x > 3){						// if the cursor is not inside the prompt
						x--;						// decrement the cursor position
					//	read_in_command[command_pointer] -= 1; // remove the last charactor from the current command
						eputc(' ', x, y);			// clear spot the screen					
					}
				} else if (strcmp(ch,RETURN)==0) {	// if the special key was a return specpnt("return"))
					y++;							// increment the cursor-y position
					eputs(read_in_command, x, y);
					y++;
					//read_in_command = "";
					memset(read_in_command,0x0,sizeof(read_in_command));
					x=0;
				/*	command_info = interpret_command(read_in_command, x, y);
					y+=command_info.y_moved;
				*/	x=3;							// move the cursor to the home position
					eputs(">> ", 0, y);				// try to clear spot the screen					
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
	return 0;
}


// all commands are assumed to return an array containing the number
// of lines on the y-axis the command took and the exit status
// command id that was executed :P (0 if no command was executed; ie, the command does not exist)
// and an exit message, if any

struct command_return_struct * interpret_command(char * read_command, int x, int y) {
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
	}	*//*
	if (strcmp(read_command, 'echo') == 0) {
		crs = echo(x,y);
/*		crs.y_moved = 2;
		crs.command_id = 1;
		crs.command_message = 'SUCCESS';
		crs.command_status = 0;
	} else {
		crs.y_moved = 0;
		crs.command_id = 0;
		crs.command_message = 'NOT_FOUND';
		crs.command_status = 1;
	}
*///	return *crs; // return the various 
}


/*
int echo(int x, int x);
int echo(int x, int y){}

struct command_return_struct {
	int y_moved;
	int command_status;
	int command_id;
	char * command_message;
};

struct command {
	char * function_name;
	struct command_return_struct function_pointer;
};

int y_moved;
int command_status;
int command_id;
char * command_message;
*/



void append(char *s, char c){
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}