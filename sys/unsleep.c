/* unsleep.c - unsleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * unsleep  --  remove  process from the sleep queue prematurely
 *------------------------------------------------------------------------
 */
SYSCALL	unsleep(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	struct	qent	*qptr;
	int	remain;
	int	next;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][25].syscallName = "sys_unsleep";
		syscallTable[currpid][25].syscallFreq += 1;
	}

        disable(ps);
	if (isbadpid(pid) ||
	    ( (pptr = &proctab[pid])->pstate != PRSLEEP &&
	     pptr->pstate != PRTRECV) ) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][25].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	qptr = &q[pid];
	remain = qptr->qkey;
	if ( (next=qptr->qnext) < NPROC)
		q[next].qkey += remain;
	dequeue(pid);
	if ( (next=q[clockq].qnext) < NPROC)
		sltop = (int *) & q[next].qkey;
	else
		slnempty = FALSE;
        restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][25].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
