/**
 *
 *	File:		main.c
 *
 *	Project:	DoSH
 *	Component:	Point insertion
 *
 *	Authors:	Dominic May;
 *				Lord_DeathMatch;			
 *				Mause
 *
 *	Description:	DoSH = Doms Own SHell
 *
 **/

// system includes
#include "stdlib.h"
#include "ext/screen.h"
#include "string.h"

// project includes
#include "version.h"
#include "defines.h"
#include "doms_stdlib.h"
// #include "extern_table.h"

// reckon i can get it to compile under gcc?
#ifdef printf
 eputs = printf
#endif


int main() {
	// define variables :)
	int hwcount;
	int ch; 					// contains the most recent character entered into the keyboard
	int ch_stat;				// contains boolean indicating whether or not the current ch is special
	int breaker = false;

	struct command_return_struct *command_info;

	char read_in_command[COMMAND_LENGTH];
	int command_pointer;
	char *command_fragment;

	// char previous_commands[REM_COMMAND][COMMAND_LENGTH];
	int previous_command_pointer;

	// line buffer :)
	char * lines[16];

	// points to where the cursor is
	int x=0;
	int y=0;

	// returns an array, first value is exit status, second is y value, third is x value
	int from_return[3];

	eputs("Loading", 0, 0);	// Display loading screen
	
	//hwcount = find_hw(); 	// currently does not work, not sure why
	scrn_border_colour(0); 	// set screen border to black (hopefully)
	eputc('.', 8, 0);		// Display second point of loading screen
	eputc('.', 9, 0);		// Display third point of loading screen

	//atlas_cls(); 			// clear code stolen (sorry) from the AtlasOS O.S.
	cls(); 					// clear screen
	//asm_cls(); 			// assembly based screen cleaner; supposed to be much faster
    						// although, i think it is bugging out a bit though

	eputs("DoSH version ", x, y);  	// display DoSH title
	eputs(GITVERSION, x+13, y);  	// display DoSH version

	x=3;
	y=1;
	//clock_delay(1, clock_int);	// clock delay, does not work

	eputs(">> ", 0, 1);	

	while (!breaker){ 									// primary application loop
		ch=0;										// reset ch
		ch = doms_getch();   						// get a character in the form of an int from the keyboard
		ch_stat = if_special(ch);					// determine if ch is a special key
		//if (y==32){
		//	atlas_scroll();
		if (!true){
			// this is the scrolling logic will end up :P
		} else {
			while (ch!=0){								// while ch is not 0
				if (ch_stat!=0){						// if is not a special key, print it to the terminal
					eputc(ch, x, y);					// print the ch to the terminal
					if (strlen(read_in_command)<COMMAND_LENGTH-1){
						read_in_command[command_pointer] = ch; // append the ch the the current command
						command_pointer++;
					}
					x++;					// increment the cursor position
				} else if (ch_stat == 0) {	// if ch was a special key
					if (ch == BACKSPACE) {	// if the special key was a backspace
						if (x > 3){			// if the cursor is not within the prompt
							x--;			// decrement the cursor position
							command_pointer--;	// decrement the command pointer
							read_in_command[command_pointer] = '\0'; // remove the last character from the current command
							eputc(' ', x, y);	// clear spot the screen					
						}
					} else if (ch == RETURN) {	// if the special key was a return
						
						// put the current command at the front of the command memory
						// rightRotatebyOne(previous_commands, REM_COMMAND);

						if (true){//(read_in_command[0] != '\0'){ //{//(strcmp(read_in_command[1],'\0')!=0)
							y++;							// increment the cursor-y position, standard :P
							x=0;
							
							command_fragment = strtok(read_in_command, " ");
							if (read_in_command[0]!=NULL){
								if 		  (strcmp(read_in_command, "exit") == 0){ // this is technically a built-in, but it is easy to implement here :P
									x=0;
									y=0;
									breaker = true;
									break;
								} else if (strcmp(read_in_command, "echo") == 0) { // another thing that is technically a built-in, but it is here for testing purposes :P
									eputs(read_in_command.substring(5,COMMAND_LENGTH), x, y); y++;
									// command_fragment = strtok(read_in_command, ' ');
									// while (strcmp(command_fragment,NULL)!=0) {
									// 	eputs(command_fragment, x, y); y++;
									// 	command_fragment = strtok(NULL, ' ');
									// }
								} else if (strcmp(read_in_command, "cls") == 0 || strcmp(read_in_command, "clear") == 0) {
									cls();
									y=0;
								} else if (strcmp(read_in_command, "test") == 0) {
									eputs("BLEEP! BLOOP! TESTING!", x, y); y++;
								} else if (strcmp(read_in_command, "help") == 0) {
									eputs(HELP_RESPONSE, x, y); y++;
								} else {
									eputs(COMMAND_NOT_FOUND, x, y); y++;
								}
									//else {
						/*			command_info = interpret_command(read_in_command, x, y);
									y+=command_info.y_moved;
						*/			x=3;					// move the cursor to the home position
									//y++;
									//clear_cmd_bffr(read_in_command, command_pointer);
									while (command_pointer!=0){						// this will tidy up the command buffer :D
										read_in_command[command_pointer] = '\0';
										command_pointer--;
									}
									//clr_cmd_bffr();
									read_in_command[0] = '\0'; // ensure the first character of the command buffer is clean
									eputs(">> ", 0, y);
								// }
							}
						}


					} else if (strcmp(ch, ARROW_LEFT)) {
						if (x > 3){	x--; }				// decrement the cursor position
					} else if (strcmp(ch, ARROW_RIGHT)) {
						if (x > 3){ x++; }				// increment the cursor position
					} else if (strcmp(ch, ARROW_UP)) {
						// if (x > 3){ x++; }				// increment the cursor position

					} else {
						//eputc('?', x, y);				// print a ? char for an un-handled special key :P
						//x++;							// increment the cursor position
					}
				}
				ch=0;									// reset ch
			}
		}
	}
	cls();
	eputs(SHUTDOWN_MESSAGE, 0, 0);
	abort();
	return 0;
}


// all commands are assumed to return an array containing the number
// of lines on the y-axis the command took and the exit status
// command id that was executed :P (0 if no command was executed; ie, the command does not exist)
// and an exit message, if any
// struct command_return_struct * 
/*
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
	}	/
	if (strcmp(read_command, "echo") == 0) {
		crs = echo(x,y);
/*		crs.y_moved = 2;
		crs.command_id = 1;
		crs.command_message = 'SUCCESS';
		crs.command_status = 0;
/	} else {
		crs.y_moved = 0;
		crs.command_id = 0;
		crs.command_message = 'NOT_FOUND';
		crs.command_status = 1;
	}
	return crs; // return the various 
}
*/

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
