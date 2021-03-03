#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

static unsigned long *esp;

void printprocstks(int priority) {
    struct pentry *process;

    int processID;

    kprintf("\nvoid printprocstks(int priority)");

    for (processID = 0; processID < NPROC; processID++) {
        process = &proctab[processID];

        if((process->pstate) != PRFREE && (process->pprio > priority)) {
            kprintf("\nProcess\t[%s]\n",process->pname);	
            kprintf("\tpid: %d\n",processID);		
            kprintf("\tpriority: %d\n",process->pprio);
            kprintf("\tbase: 0x%08x\n",process->pbase);	
            kprintf("\tlimit: 0x%08x\n",process->plimit);
            kprintf("\tlen: %d\n",process->pstklen);

            if(process -> pstate == PRCURR) {
				asm("movl %esp, esp");
                kprintf("\tpointer: 0x%08x\n",esp);
			}
			else {
                kprintf("\tpointer: 0x%08x\n",process -> pesp);
			}	
        }
    }
}