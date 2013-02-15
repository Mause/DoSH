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

// system specific includes
#include "stdlib.h"
#include "ext/screen.h"
#include "string.h"

// project specific includes
#include "version.h"
#include "defines.h"
#include "doms_stdlib.h"
// #include "extern_table.h"

// device libraries
#include "libfloppy.h"


int main() {
	// define variables :)
	int ch; 					// contains the most recent character entered into the keyboard
	int ch_stat;				// contains boolean indicating whether or not the current ch is special
	int breaker = 0;			// treated as boolean. primary loop exist when == 1
	char * current_user;		// contains username of current user

	char read_in_command[COMMAND_LENGTH];
	int command_pointer;
	// char *command_fragment;

	// char previous_commands[REM_COMMAND][COMMAND_LENGTH];
	// int previous_command_pointer;

	// line buffer :)
	// char * lines[16];

	// points to where the cursor is
	int x=0;
	int y=0;

	// initialise varaibles

	current_user = "mause";


	eputs("Loading", 0, 0);	// Display loading screen
	eputc('.', 8, 0);		// Display first point of loading screen
	// hwcount = find_hw();
	find_hw();
	// scrn_border_colour(0); 	// set screen border to black (hopefully)
	eputc('.', 9, 0);		// Display second point of loading screen

	//atlas_cls(); 			// clear code stolen (sorry) from the AtlasOS O.S.
	cls(); 					// clear screen
	//asm_cls(); 			// assembly based screen cleaner; supposed to be much faster
    						// although, i think it is bugging out a bit though

	eputs("DoSH version ", x, y);  	// display DoSH title
	eputs(GITVERSION, x+13, y);  	// display DoSH git revision
	// eputs("Username:", )

	x=3;
	y=1;
	//clock_delay(1, clock_int);	// clock delay, does not work

	eputs(">> ", 0, 1);
	// return 0;
	while (breaker != 1){ 								// primary application loop
		ch=0;										// reset ch
		ch = doms_getch();   						// get a character in the form of an int from the keyboard
		ch_stat = if_special(ch);					// determine if ch is a special key
		// if (y == 32){
		// 	atlas_scroll();
		if (!true){
			// this is the scrolling logic will end up :P
		} else {
			while (ch!=0){								// while ch is not null/empty
				if (ch_stat == 0){						// if is not a special key, print it to the terminal
					eputc(ch, x, y);					// print the ch to the terminal
					if (strlen(read_in_command) < COMMAND_LENGTH - 1){
						read_in_command[command_pointer] = ch; // append the ch the the current command
						command_pointer++;
					}
					x++;					// increment the cursor position
				} else if (ch_stat == 1) {	// if ch was a special key
					if (ch == BACKSPACE) {	// if the special key was a backspace
						if (x > 3){			// if the cursor is not within the prompt
							x--;			// decrement the cursor position
							command_pointer--;	// decrement the command pointer
							read_in_command[command_pointer] = '\0'; // remove the last character from the current command
							eputc(' ', x, y);	// clear spot the screen
						}
					} else if (ch == RETURN) {	// if the special key was a return

						if (true){//(read_in_command[0] != '\0'){ //{//(strcmp(read_in_command[0],'\0')!=0)
							// put the current command at the front of the command memory
							// rightRotatebyOne(previous_commands, REM_COMMAND);
							y++;							// increment the cursor-y position, standard :P
							x=0;
							// command_fragment = strtok(read_in_command, " ");
							if (read_in_command[0]!=NULL){
								if 		  (strcmp(read_in_command, "exit") == 0 || strcmp(read_in_command, "shutdown") == 0){ // this is technically a built-in, but it is easy to implement here :P
									x=0;
									y=0;
									breaker = 1;
									break;
								} else if (strcmp(read_in_command, "echo") == 0) { // another thing that is technically a built-in, but it is here for testing purposes :P
									// TODO: Fix this command
									// next line is reference
									// char *substring(size_t start, size_t stop, const char *src, char *dst, size_t size)
									// eputs(substring(read_in_command, 5, COMMAND_LENGTH), x, y); y++;
									// command_fragment = strtok(read_in_command, ' ');
									// while (strcmp(command_fragment,NULL)!=0) {
									// 	eputs(command_fragment, x, y); y++;
									// 	command_fragment = strtok(NULL, ' ');
									// }
								} else if (strcmp(read_in_command, "cls") == 0 || strcmp(read_in_command, "clear") == 0) {
									cls();
									y=0;
								} else if (strcmp(read_in_command, "flp") == 0){
									if (strcmp(read_in_command, "flp s") == 0){
										eputs(get_human_readable_state(), x, y); y++;
									} else if (strcmp(read_in_command, "flp r")) {
										eputs("Not implemented", x, y); y++;
									} else if (strcmp(read_in_command, "flp w")) {
										eputs("Not implemented", x, y); y++;
									}
								} else if (strcmp(read_in_command, "test") == 0) {
									eputs("BLEEP! BLOOP! TESTING!", x, y); y++;
								} else if (strcmp(read_in_command, "wait") == 0) {
									clock_delay(1000);
								} else if (strcmp(read_in_command, "whoami") == 0){
									eputs(current_user, x, y); y++;
								} else if (strcmp(read_in_command, "help") == 0) {
									eputs(HELP_RESPONSE, x, y); y++;
								} else {
									eputs(COMMAND_NOT_FOUND, x, y); y++;
								}

								x=3;											// move the cursor to the home position
								while (command_pointer!=0){						// this loop will tidy up the command buffer :D
									read_in_command[command_pointer] = '\0';
									command_pointer--;
								}

								read_in_command[0] = '\0'; // ensure the first character of the command buffer is clean
								eputs(">> ", 0, y);
							}
						}
					} else if (strcmp(ch, ARROW_LEFT)) {
						if (x > 3){	x--; }				// decrement the cursor position
					} else if (strcmp(ch, ARROW_RIGHT)) {
						if (x > 3){ x++; }				// increment the cursor position
					} else if (strcmp(ch, ARROW_UP)) {
						// once i have previous command storage working,
						// this is where the recalling logic will end up
					} else if (strcmp(ch, ARROW_DOWN)) {

					// } else {
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
