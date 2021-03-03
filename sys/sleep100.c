/* sleep100.c - sleep100 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * sleep100  --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep100(int n)
{
	STATWORD ps;  
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][20].syscallName = "sys_sleep100";
		syscallTable[currpid][20].syscallFreq += 1;
	}  

	if (n < 0  || clkruns==0) {
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][20].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep100(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*10);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][20].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
