/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][9].syscallName = "sys_resume";
		syscallTable[currpid][9].syscallFreq += 1;
	}
	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][9].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][9].syscallAvgExecTime += (endtime - starttime);
	}
	return(prio);
}
