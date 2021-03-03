/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][12].syscallName = "sys_send";
		syscallTable[currpid][12].syscallFreq += 1;
	}

	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][12].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][12].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
