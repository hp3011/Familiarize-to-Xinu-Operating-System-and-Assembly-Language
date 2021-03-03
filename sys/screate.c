/* screate.c - screate, newsem */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
LOCAL int newsem();

/*------------------------------------------------------------------------
 * screate  --  create and initialize a semaphore, returning its id
 *------------------------------------------------------------------------
 */
SYSCALL screate(int count)
{
	STATWORD ps;    
	int	sem;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][15].syscallName = "sys_screate";
		syscallTable[currpid][15].syscallFreq += 1;
	}

	disable(ps);
	if ( count<0 || (sem=newsem())==SYSERR ) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][15].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	semaph[sem].semcnt = count;
	/* sqhead and sqtail were initialized at system startup */
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][15].syscallAvgExecTime += (endtime - starttime);
	}
	return(sem);
}

/*------------------------------------------------------------------------
 * newsem  --  allocate an unused semaphore and return its index
 *------------------------------------------------------------------------
 */
LOCAL int newsem()
{
	int	sem;
	int	i;

	for (i=0 ; i<NSEM ; i++) {
		sem=nextsem--;
		if (nextsem < 0)
			nextsem = NSEM-1;
		if (semaph[sem].sstate==SFREE) {
			semaph[sem].sstate = SUSED;
			return(sem);
		}
	}
	return(SYSERR);
}
