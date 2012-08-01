/**
 *
 *	File:		defines.h
 *
 *	Project:	DoSH v.10
 *	Component:	definitions
 *
 *	Authors:	Dominic May;
 *				Lord_DeathMatch;			
 *				Mause
 *
 *	Description:	contains definitions for structs and some settings :)
 *
 **/

// Structs :D

#ifndef __DOSH_DEFINES_H
#define __DOSH_DEFINES_H

struct command_return_struct {
	int y_moved;
	int command_status;
	int command_id;
	char * command_message;
};

// Constants :)

// only one display is supported atm
#define MAX_DISPLAYS 1 // when set to zero, assumed unlimited :D
#define COMMAND_LENGTH 30
#define REM_COMMAND 3 // how many commands to remember; will be used to define the size of an array that stores the previous commands :P
// COMMAND_LENGTH * REM_COMMAND = 90


// define some basics
//typedef int bool;
#define true 1;
#define false 0;

#define SUCCESS 0;
#define FAILURE 1;

// various keyboard codes ;)
#define BACKSPACE 0x10;	// Backspace
#define RETURN 0x11;	// Return
#define INSERT 0x12;	// Insert
#define DELETE 0x13;	// Delete
#define ARROW_UP 0x80;	// Arrow up
#define ARROW_DOWN 0x81;	// Arrow down
#define ARROW_LEFT 0x82;	// Arrow left
#define ARROW_RIGHT 0x83;	// Arrow right
#define SHIFT 0x90;	// Shift
#define CONTROL 0x91;	// Control


// the defines that follow are user facing, and will be used to respond to particular situations
#define COMMAND_NOT_FOUND "Command not found"

#define HELP_RESPONSE "exit,echo,cls,test,help"

#define SHUTDOWN_MESSAGE "It is now safe to turn off your computer"


#endif