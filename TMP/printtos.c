#include <stdio.h>
#include <lab0.h>

extern int currpid;

static unsigned long *esp;
static unsigned long *ebp;

void printtos()
{
    
    asm("movl %ebp, ebp");
    asm("movl %esp, esp");
    int i;
    kprintf("\nvoid printtos()\n");

    kprintf("Before[0x%08x] = 0x%08x\n", ebp+2, *(ebp+2));
    kprintf("After[0x%08x] = 0x%08x\n", ebp, *ebp);

    for (i=0; i<4; i++){
        if ((esp+i)==ebp)
            break;
        kprintf("\telement[0x%08x] = 0x%08x\n", esp+i, *(esp+i));
    }
}