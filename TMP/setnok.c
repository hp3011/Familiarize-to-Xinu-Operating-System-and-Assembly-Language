/* setnok.c - setnok */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  setnok  -  set next-of-kin (notified at death) for a given process
 *------------------------------------------------------------------------
 */
SYSCALL	setnok(int nok, int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][14].syscallName = "sys_setnok";
		syscallTable[currpid][14].syscallFreq += 1;
	}

	disable(ps);
	if (isbadpid(pid)) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][14].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	pptr = &proctab[pid];
	pptr->pnxtkin = nok;
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][14].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
