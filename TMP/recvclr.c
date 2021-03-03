/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{
	STATWORD ps;    
	WORD	msg;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][7].syscallName = "sys_recvclr";
		syscallTable[currpid][7].syscallFreq += 1;
	}
	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][7].syscallAvgExecTime += (endtime - starttime);
	}
	return(msg);
}
