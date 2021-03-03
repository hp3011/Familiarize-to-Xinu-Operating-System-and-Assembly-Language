/* sreset.c - sreset */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;

/*------------------------------------------------------------------------
 *  sreset  --  reset the count and queue of a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL sreset(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	int	pid;
	int	slist;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][22].syscallName = "sys_sreset";
		syscallTable[currpid][22].syscallFreq += 1;
	}

	disable(ps);
	if (isbadsem(sem) || count<0 || semaph[sem].sstate==SFREE) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][22].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid=getfirst(slist)) != EMPTY)
		ready(pid,RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][22].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
