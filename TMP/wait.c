/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][26].syscallName = "sys_wait";
		syscallTable[currpid][26].syscallFreq += 1;
	}

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][26].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][26].syscallAvgExecTime += (endtime - starttime);
		}
		return pptr->pwaitret;
	}
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][26].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
