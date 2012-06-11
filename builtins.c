/**
 *
 *	File:		dosh.c
 *
 *	Project:	DoSH v.10
 *	Component:	Shell built-ins
 *
 *	Authors:	Dominic May;
 *				Lord_DeathMatch;			
 *				Mause
 *
 *	Description:	DoSH = Doms Own SHell
 *
 **/

int echo(int x, int x);
struct command echof;
echof.function_name = "echo";
echof.function_pointer = echo;
int echo(int x, int y){}