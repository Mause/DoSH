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
// prototypes :D

struct command_return_struct echo(int x, int y){
	struct command_return_struct crs;
	int i = 50;
	while (i!=0){i--;}
	crs.y_moved=1;
	crs.command_id = 1;
	crs.command_message = 'SUCCESS';
	crs.command_status = 0;
	return crs;
}
