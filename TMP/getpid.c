/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][2].syscallName = "sys_getpid";
		syscallTable[currpid][2].syscallFreq += 1;
		endtime = ctr1000;
		syscallTable[currpid][2].syscallAvgExecTime += (endtime - starttime);
	}

	return(currpid);
}
