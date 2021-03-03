/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{
	STATWORD ps;    
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][21].syscallName = "sys_sleep1000";
		syscallTable[currpid][21].syscallFreq += 1;
	}

	if (n < 0  || clkruns==0) {
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][21].syscallAvgExecTime += (endtime - starttime);
		}
	    return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][21].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
