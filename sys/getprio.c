/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][3].syscallName = "sys_getprio";
		syscallTable[currpid][3].syscallFreq += 1;
	}
	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][3].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][3].syscallAvgExecTime += (endtime - starttime);
	}
	return(pptr->pprio);
}
