/* recvtim.c - recvtim */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  recvtim  -  wait to receive a message or timeout and return result
 *------------------------------------------------------------------------
 */
SYSCALL	recvtim(int maxwait)
{
	STATWORD ps;
	struct	pentry	*pptr;
	int	msg;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][8].syscallName = "sys_recvtim";
		syscallTable[currpid][8].syscallFreq += 1;
	}
	if (maxwait<0 || clkruns == 0)
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][8].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait		*/
	        insertd(currpid, clockq, maxwait*1000);
		slnempty = TRUE;
		sltop = (int *)&q[q[clockq].qnext].qkey;
	        pptr->pstate = PRTRECV;
		resched();
	}
	if ( pptr->phasmsg ) {
		msg = pptr->pmsg;	/* msg. arrived => retrieve it	*/
		pptr->phasmsg = FALSE;
	} else {			/* still no message => TIMEOUT	*/
		msg = TIMEOUT;
	}
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][8].syscallAvgExecTime += (endtime - starttime);
	}
	return(msg);
}
