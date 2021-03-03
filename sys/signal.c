/* signal.c - signal */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * signal  --  signal a semaphore, releasing one waiting process
 *------------------------------------------------------------------------
 */
SYSCALL signal(int sem)
{
	STATWORD ps;    
	register struct	sentry	*sptr;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][16].syscallName = "sys_signal";
		syscallTable[currpid][16].syscallFreq += 1;
	}

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][16].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	if ((sptr->semcnt++) < 0)
		ready(getfirst(sptr->sqhead), RESCHYES);
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][16].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
