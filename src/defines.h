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

// customs types
typedef struct {
    int slot;
} hw_clock;

typedef struct {
    int slot;
} hw_floppy_drive;

typedef struct {
    hw_clock clock;
    hw_floppy_drive floppy;
    int hwcount;
} hardware_obj;


typedef struct {
    char * username;
    char * ENV_KEYS[10];
    char * ENV_VALUES[10];
    hardware_obj hardware;
} session;

typedef struct {
    int y_value;
    int command_status;
    int command_id;
    char * command_message;
    int should_shutdown;
} command;


/* const command COMMAND_STRUCT_TEMPLATE = {
//     1,
//     SUCCESS,
//     0,
//     "",
//     0
// };
*/

// typedef int bool;

// Constants :)

#ifndef GITVERSION

 #define GITVERSION "beta"

#endif


// only one display is supported atm
// when set to zero, assumed unlimited :D (currently unused)
#define MAX_DISPLAYS 1

#define COMMAND_LENGTH 30

#define REM_COMMAND 30
// how many commands to remember; will be used to define the size of an array that stores the previous commands :P = 90
#define MEMORY_USED_BY_REMEMBERED_COMMANDS = COMMAND_LENGTH * REM_COMMAND


// define some basics


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

#define INPUT_IS_EQUAL(command) (strncmp(read_in_command, command, COMMAND_LENGTH) == 0)

#endif
