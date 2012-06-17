/**
 *
 *	File:		builtins.c
 *
 *	Project:	DoSH v.10
 *	Component:	Shell built-ins
 *
 *	Authors:	Dominic May;
 *				Lord_DeathMatch;			
 *				Mause
 *
 *	Description:	contains built-in shell commands
 *
 **/

#ifndef __DOSH_BUILTINS_C
#define __DOSH_BUILTINS_C

#include "stdlib.h"
#include "defines.h"

// will echo arguments to the command line
// will hopefully be used in some shell script clone :D
struct command_return_struct echo(int x, int y){
	struct command_return_struct crs;
	int i = 50;
	while (i!=0){i--;}
	crs.y_moved=1;
	crs.command_id = 1;
	crs.command_message = "SUCCESS";
	crs.command_status = 0;
	return crs;
}

#endif
