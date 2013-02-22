/**
 *
 *  File:       builtins.c
 *
 *  Project:    DoSH v.10
 *  Component:  Shell built-ins
 *
 *  Authors:    Dominic May;
 *              Lord_DeathMatch;
 *              Mause
 *
 *  Description:    contains built-in shell commands
 *
 **/

#ifndef __DOSH_BUILTINS_H
#define __DOSH_BUILTINS_H

#include "defines.h"
#include "libfloppy.h"

command execute_command(char * read_in_command, int x, int y, session *current_session);
command command_wait(char * read_in_command, int x, int y, session *current_session);
command command_cls(char * read_in_command, int x, int y, session *current_session);
command command_help(char * read_in_command, int x, int y, session *current_session);
command command_whoami(char * read_in_command, int x, int y, session *current_session);
command command_test(char * read_in_command, int x, int y, session *current_session);
command command_shutdown(char * read_in_command, int x, int y, session *current_session);
command command_echo(char * read_in_command, int x, int y, session *current_session);
command command_flp(char * read_in_command, int x, int y, session *current_session);
command command_poof(char * read_in_command, int x, int y, session *current_session);
command command_hw(char * read_in_command, int x, int y, session *current_session);

#endif
