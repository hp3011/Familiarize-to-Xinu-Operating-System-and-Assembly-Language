/* signaln.c - signaln */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  signaln -- signal a semaphore n times
 *------------------------------------------------------------------------
 */
SYSCALL signaln(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][17].syscallName = "sys_signaln";
		syscallTable[currpid][17].syscallFreq += 1;
	}

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE || count<=0) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][17].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	for (; count > 0  ; count--)
		if ((sptr->semcnt++) < 0)
			ready(getfirst(sptr->sqhead), RESCHNO);
	resched();
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][17].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
