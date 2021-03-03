/* suspend.c - suspend */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  suspend  --  suspend a process, placing it in hibernation
 *------------------------------------------------------------------------
 */
SYSCALL	suspend(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority returned		*/
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][24].syscallName = "sys_suspend";
		syscallTable[currpid][24].syscallFreq += 1;
	}

	disable(ps);
	if (isbadpid(pid) || pid==NULLPROC ||
	 ((pptr= &proctab[pid])->pstate!=PRCURR && pptr->pstate!=PRREADY)) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][24].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	if (pptr->pstate == PRREADY) {
		pptr->pstate = PRSUSP;
		dequeue(pid);
	}
	else {
		pptr->pstate = PRSUSP;
		resched();
	}
	prio = pptr->pprio;
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][24].syscallAvgExecTime += (endtime - starttime);
	}
	return(prio);
}
