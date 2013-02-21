int get_floppy_slot(){
    int floppy_slot;
    __asm {
        .IMPORT floppy_slot
        set <floppy_slot>, [floppy_slot]
        ; c-land ^       asm-land ^
    }
    return floppy_slot;
}



int read(int handle, void *buffer, int nbyte){
    int floppy_slot;
    floppy_slot = get_floppy_slot();
    return floppy_slot;
}



// There's no floppy in the drive.
#define STATE_NO_MEDIA 0x0000
// The drive is ready to accept commands.
#define STATE_READY 0x0001
// Same as ready, except the floppy is write protected.
#define STATE_READY_WP 0x0002

int get_state(){
    int cur_state;
    __asm{
        .IMPORT floppy_slot
        set push, B
        set push, C
        HWI [floppy_slot]
        set <cur_state>, B
        set B, pop
        set C, pop
    }
    return cur_state;
}


char * get_human_readable_state(){
    int cur_state = get_state();
    if (cur_state == STATE_NO_MEDIA) {
        return "STATE_NO_MEDIA";
    } else if (cur_state == STATE_READY) {
        return "STATE_READY";
    } else if (cur_state == STATE_READY_WP) {
        return "STATE_READY_WP";
    } else {
        return "STATE_UNKNOWN";
    }
}
