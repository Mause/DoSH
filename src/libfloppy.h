#ifndef __LIBFLOPPY_H
#define __LIBFLOPPY_H
#include "defines.h"

int read(int handle, void *buffer, int nbyte);
int get_human_readable_state(session current_session);
int get_floppy_state(session current_session);

#endif
