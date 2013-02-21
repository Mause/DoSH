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

// standard library includes
#include "string.h"
#include "stdlib.h"
#include "ext/screen.h"
#include "stdio.h"

// DoSH includes
#include "builtins.h"
#include "defines.h"
#include "libfloppy.h"
#include "doms_stdlib.h"

int indexOf(char * arr[], char * string, int numElements){
    int i;

    for(i=0; i<numElements; ++i) {
        if (strcmp(arr[i], string) == 0) {
            return i;
        }
    }

    if (i >= numElements) {
        return -1;
    }
}

command execute_command(char * read_in_command, int x, int y, state current_state){
    // this function works out which function to call depending on user input :D
    int function_index = -1;
    command return_struct;
    // char test[100];

    const char *COMMANDS_KEYS[8] = {
        "whoami",
        "shutdown",
        "test",
        "wait",
        "help",
        "echo",
        "cls",
        "flp",
    };

    unsigned int numElements = 8;

    command (*COMMANDS_FUNCTIONS[8]) (char * read_in_command, int x, int y, state current_state) = {
        command_whoami,
        command_shutdown,
        command_test,
        command_wait,
        command_help,
        command_echo,
        command_cls,
        command_flp,
    };

    for(function_index=0; function_index<numElements; ++function_index) {
        if (strncmp(COMMANDS_KEYS[function_index], read_in_command, strlen(COMMANDS_KEYS[function_index]) - 1) == 0) {
            break;
        }
    }

    if (function_index >= numElements) {
        function_index = -1;
    }

    if (function_index > -1){
        return_struct.y_value = y;
        return_struct = (****COMMANDS_FUNCTIONS[function_index])(
            read_in_command, x, y, current_state);
    } else {
        eputs(COMMAND_NOT_FOUND, x, y); y++;
        return_struct.y_value = y;
    }

    return return_struct;
}


command command_wait(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    clock_delay(1000);

    return_struct.y_value = y;
    return return_struct;
}

command command_cls(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    cls();
    y=0;

    return_struct.y_value = y;
    return return_struct;
}

command command_help(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    eputs(HELP_RESPONSE, x, y); y++;

    return_struct.y_value = y;
    return return_struct;
}

command command_whoami(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    eputs(current_state.current_username, x, y); y++;

    return_struct.y_value = y;
    return return_struct;
}


command command_test(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    eputs("BLEEP! BLOOP! TESTING!", x, y);
    y++;

    return_struct.y_value = y;
    return return_struct;
}


command command_shutdown(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    return_struct.y_value=y;
    return_struct.should_shutdown = true;

    return return_struct;
}


command command_echo(char * read_in_command, int x, int y, state current_state){
    command return_struct;
    // this line cannot be implemented properly until we have a strtok implementation

    // TODO: Fix this command
    // next line is reference
    // char *substring(size_t start, size_t stop, const char *src, char *dst, size_t size)
    // eputs(substring(read_in_command, 5, COMMAND_LENGTH), x, y); y++;
    // command_fragment = strtok(read_in_command, ' ');
    // while (strcmp(command_fragment,NULL)!=0) {
    //  command_fragment = strtok(NULL, ' ');
    // }

    eputs(read_in_command, x, y++);

    return_struct.y_value = y;
    return return_struct;
}



command command_flp(char * read_in_command, int x, int y, state current_state){
    command return_struct;

    if (INPUT_IS_EQUAL("flp s")){
        eputs(get_human_readable_state(), x, y++);
        return_struct.command_status = SUCCESS;
    } else if (INPUT_IS_EQUAL("flp r")) {
        eputs("Not implemented", x, y++);
        return_struct.command_status = FAILURE;
    } else if (INPUT_IS_EQUAL("flp w")) {
        eputs("Not implemented", x, y++);
        return_struct.command_status = FAILURE;
    } else {
        eputs("Please provide w,r or s as an", x, y++);
        eputs("argument", x, y++);
        return_struct.command_status = FAILURE;
    }

    return_struct.y_value = y;
    return_struct.command_status = SUCCESS;
    return_struct.command_message = "";

    return return_struct;
}


#endif
