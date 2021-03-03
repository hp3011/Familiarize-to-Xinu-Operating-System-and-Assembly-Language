/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{
	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][11].syscallName = "sys_sdelete";
		syscallTable[currpid][11].syscallFreq += 1;
	}

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][11].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][11].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
