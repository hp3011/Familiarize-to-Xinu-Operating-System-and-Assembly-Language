/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{
	STATWORD ps;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][19].syscallName = "sys_sleep10";
		syscallTable[currpid][19].syscallFreq += 1;
	}    
	if (n < 0  || clkruns==0) {
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][19].syscallAvgExecTime += (endtime - starttime);
		}
	    return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][19].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
