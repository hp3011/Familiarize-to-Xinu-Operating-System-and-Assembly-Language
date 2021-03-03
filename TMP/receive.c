/* receive.c - receive */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return it
 *------------------------------------------------------------------------
 */
SYSCALL	receive()
{
	STATWORD ps;    
	struct	pentry	*pptr;
	WORD	msg;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][6].syscallName = "sys_receive";
		syscallTable[currpid][6].syscallFreq += 1;
	}

	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait for one	*/
		pptr->pstate = PRRECV;
		resched();
	}
	msg = pptr->pmsg;		/* retrieve message		*/
	pptr->phasmsg = FALSE;
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][6].syscallAvgExecTime += (endtime - starttime);
	}
	return(msg);
}
