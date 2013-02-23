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
 *	Description: contains built-in shell commands
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


command execute_command(char * read_in_command, int x, int y, session *current_session){
    // this function works out which function to call depending on user input :D
    int function_index = -1;
    command return_struct;

    const char *COMMANDS_KEYS[9] = {
        "shutdown",
        "whoami",
        "test",
        "wait",
        "help",
        "echo",
        "cls",
        "flp",
        "hw",
    };

    unsigned int numElements = 9;

    command (*COMMANDS_FUNCTIONS[9]) (char * read_in_command, int x, int y, session *current_session) = {
        command_shutdown,
        command_whoami,
        command_test,
        command_wait,
        command_help,
        command_echo,
        command_cls,
        command_flp,
        command_hw,
    };

    return_struct.should_shutdown = false;

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
        return_struct = (****COMMANDS_FUNCTIONS[function_index])(read_in_command, x, y, &current_session);
    } else {
        eputs(COMMAND_NOT_FOUND, x, y++);
        return_struct.y_value = y;
    }

    return return_struct;
}


command command_wait(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    return_struct.should_shutdown = false;

    // this does not work at all
    clock_delay(1000, current_session->hardware.clock.slot);

    return_struct.y_value = y;
    return return_struct;
}


command command_cls(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    return_struct.should_shutdown = false;

    cls();
    y = 0;

    return_struct.y_value = y;
    return return_struct;
}


command command_hw(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    char * output_string = "";
    return_struct.should_shutdown = false;

    sprintf(
        output_string, "Clock slot; %d, hwcount; %d",
        current_session->hardware.clock.slot, current_session->hardware.hwcount);
    // sprintf(output_string, "%s", current_session->username);
    eputs(output_string, x, y++);

    return_struct.y_value = y;
    return return_struct;
}


command command_help(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    return_struct.should_shutdown = false;

    eputs(HELP_RESPONSE, x, y); y++;

    return_struct.y_value = y;
    return return_struct;
}


command command_whoami(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    char * output_string = "";
    return_struct.should_shutdown = false;

    sprintf(output_string, "Username; %s", current_session->username);
    eputs(output_string, x, y++);

    return_struct.y_value = y;
    return return_struct;
}


command command_test(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    return_struct.should_shutdown = false;

    eputs("BLEEP! BLOOP! TESTING!", x, y++);

    return_struct.y_value = y;
    return return_struct;
}


command command_shutdown(char * read_in_command, int x, int y, session *current_session){
    command return_struct;

    return_struct.y_value=y;
    return_struct.should_shutdown = true;

    return return_struct;
}


command command_echo(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    return_struct.should_shutdown = false;
    // this line cannot be implemented properly until we have a strtok implementation

    // TODO: Fix this command
    // next line is reference
    // char *substring(size_t start, size_t stop, const char *src, char *dst, size_t size)
    // eputs(substring(read_in_command, 5, COMMAND_LENGTH), x, y++);
    // command_fragment = strtok(read_in_command, ' ');
    // while (strcmp(command_fragment,NULL)!=0) {
    //  command_fragment = strtok(NULL, ' ');
    // }

    eputs(read_in_command, x, y++);

    return_struct.y_value = y;
    return return_struct;
}



command command_flp(char * read_in_command, int x, int y, session *current_session){
    command return_struct;
    return_struct.should_shutdown = false;

    if (INPUT_IS_EQUAL("flp s")){
        eputs(get_human_readable_state(&current_session), x, y++);
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
