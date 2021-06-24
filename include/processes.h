#ifndef _PROCESSES_H
#include _PROCESSES_H

struct pcb {
    proc_saved_state_t* saved_state;
    struct ppage*       pages_used;
} process_control_block

#endif

