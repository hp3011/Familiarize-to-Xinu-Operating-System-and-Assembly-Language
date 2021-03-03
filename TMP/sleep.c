/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	STATWORD ps; 
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][18].syscallName = "sys_sleep";
		syscallTable[currpid][18].syscallFreq += 1;
	}   
	if (n<0 || clkruns==0) {
		if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][18].syscallAvgExecTime += (endtime - starttime);
	}
		return(SYSERR);
	}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][18].syscallAvgExecTime += (endtime - starttime);
		}
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][18].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
