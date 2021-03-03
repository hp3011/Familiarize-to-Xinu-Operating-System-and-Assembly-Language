/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
extern	struct	sentry	semaph[];
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][10].syscallName = "sys_scount";
		syscallTable[currpid][10].syscallFreq += 1;
	}
	if (isbadsem(sem) || semaph[sem].sstate==SFREE){
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][10].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][10].syscallAvgExecTime += (endtime - starttime);
	}
	return(semaph[sem].semcnt);
}
