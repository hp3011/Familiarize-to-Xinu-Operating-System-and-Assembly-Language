/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	short	*nxtdev;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][13].syscallName = "sys_setdev";
		syscallTable[currpid][13].syscallFreq += 1;
	}

	if (isbadpid(pid)){
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][13].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][13].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
