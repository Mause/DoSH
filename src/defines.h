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

// struct command_return_struct {
// 	int y_moved;
// 	int command_status;
// 	int command_id;
// 	char * command_message;
// };

// Constants :)

// only one display is supported atm
#define MAX_DISPLAYS   1    // when set to zero, assumed unlimited :D (currently unused)
#define COMMAND_LENGTH 30
#define REM_COMMAND    30   // how many commands to remember; will be used to define the size of an array that stores the previous commands :P
// COMMAND_LENGTH * REM_COMMAND = 90


// define some basics

typedef int bool;

#define true 1
#define false 0

#define SUCCESS 0
#define FAILURE 1

// various keyboard codes ;)
// Backspace
#define BACKSPACE   0x10
// Return
#define RETURN      0x11
// Insert
#define INSERT      0x12
// Delete
#define DELETE      0x13
// Arrow up
#define ARROW_UP    0x80
// Arrow down
#define ARROW_DOWN  0x81
// Arrow left
#define ARROW_LEFT  0x82
// Arrow right
#define ARROW_RIGHT 0x83
// Shift
#define SHIFT       0x90
// Control
#define CONTROL     0x91


// the defines that follow are user facing, and will be used to respond to particular situations
#define COMMAND_NOT_FOUND "Command not found"
#define HELP_RESPONSE "exit,echo,cls,test,help"
#define SHUTDOWN_MESSAGE "It is now safe to turn off your computer"

#endif
