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


// standard library includes
#include "stdlib.h"
#include "ext/screen.h"
#include "string.h"
#include "stdio.h"

// project specific includes
#include "version.h"
#include "defines.h"
#include "doms_stdlib.h"
#include "builtins.h"
// #include "extern_table.h"

// device libraries
#include "libfloppy.h"

int main() {
	typedef int bool;

	// define variables :)
	// int hwcount;
	register int ch; 					// contains the most recent character entered into the keyboard

	// contains boolean indicating whether or not the current ch is special
	bool ch_stat;

	int breaker = 0;				// treated as boolean. primary loop exist when == 1
	// char * current_user = "Mause";		// contains username of current user

	char * read_in_command;
	// [COMMAND_LENGTH]
	int command_pointer = 0;
	// sizeof(read_in_command)

	// char *command_fragment;
	// char previous_commands[REM_COMMAND][COMMAND_LENGTH];
	// int previous_command_pointer;

	// line buffer, maybe for scrolling, maybe not
	// char * lines[16];

	command return_struct;
	session current_session;

	// points to where the cursor is
	int x = 0;
	int y = 0;


	eputs("Loading", 0, 0);	// Display loading screen
	eputc('.', 8, 0);		// Display first point of loading screen
	// hwcount = find_hw();
	find_hw(&current_session);
	// scrn_border_colour(0); 	// set screen border to black (hopefully)
	eputc('.', 9, 0);		// Display second point of loading screen

	//atlas_cls(); 			// clear code stolen (sorry) from the AtlasOS O.S.
	cls(); 					// clear screen
	//asm_cls(); 			// assembly based screen cleaner; supposed to be much faster
    						// although, i think it is bugging out a bit though

	eputs("DoSH version ", x, y);  	// display DoSH title
	eputs(GITVERSION, x+13, y);  	// display DoSH git revision

	// try authentication
	// eputs("Username:", 0, y+1);
	// for now, stick with a static username
	current_session.username = "Mause";

	x = 3;
	y++;

	// clock delay, does not work, will make the screen flash colours :(
	// clock_delay(5);

	eputs(">> ", 0, 1);

	while (breaker != 1){							// primary application loop
		ch=0;										// reset ch
		ch = doms_getch();   						// get a character in the form of an int from the keyboard
		ch_stat = if_special(ch);					// determine if ch is a special key
		// if (y == 32){
		// 	atlas_scroll();
		if (0 == 1){
			// this is the scrolling logic will end up :P
		} else {
			if (ch != 0){ 							// while ch is not null/empty
				if (ch_stat == false){						// if is not a special key, print it to the terminal
					eputc(ch, x, y);					// print the ch to the terminal
					// if (strlen(read_in_command) < COMMAND_LENGTH - 1){
					read_in_command[command_pointer] = ch; // append the ch the the current command
					command_pointer++;
					// }
					x++;						// increment the cursor position
				} else if (ch_stat == true) {	// if ch was a special key
					if (ch == BACKSPACE) {		// if the special key was a backspace
						if (x > 3){				// if the cursor is not within the prompt
							x--;				// decrement the cursor position
							command_pointer--;	// decrement the command pointer
							read_in_command[command_pointer] = '\0'; // remove the last character from the current command
							eputc(' ', x, y);	// clear spot the screen
						}
					} else if (ch == RETURN) {	// if the special key was a return
						read_in_command[command_pointer] = '\0';
						// put the current command at the front of the command memory
						// rotate_by_one(previous_commands, REM_COMMAND);
						// command_fragment = strtok(read_in_command, " ");
						if (read_in_command[0] != NULL){
							y++;				// increment the cursor-y position, standard :P
							x = 0;

							return_struct = execute_command(read_in_command, x, y, &current_session);
							y = return_struct.y_value;

							x = 3;											// move the cursor to the home position
							// command_pointer = COMMAND_LENGTH;
							command_pointer = 0;
							// read_in_command[0] = '\0';
							// while (command_pointer > 0){					// this loop will tidy up the command buffer :D
							// 	read_in_command[command_pointer] = '\0';
							// 	command_pointer--;
							// }
							read_in_command[0] = '\0'; // ensure the first character of the command buffer is clean

							if (return_struct.should_shutdown == true){
								breaker = 1;
								break;
							}

							eputs(">> ", 0, y);
						}

					} else if (strcmp(ch, ARROW_LEFT)) {
						if (x > 3){	x--; }				// decrement the cursor position
					} else if (strcmp(ch, ARROW_RIGHT)) {
						if (x > 3){ x++; }				// increment the cursor position
					// } else if (strcmp(ch, ARROW_UP)) {
						// once i have previous command storage working,
						// this is where the recalling logic will end up
					// } else if (strcmp(ch, ARROW_DOWN)) {

					// } else {
						//eputc('?', x, y);				// print a ? char for an un-handled special key :P
						//x++;							// increment the cursor position
					}
				}
				ch = 0;									// reset ch
			}
		}
	}
	cls();
	eputs(SHUTDOWN_MESSAGE, 0, 0);
	abort();
	return 0;
}
