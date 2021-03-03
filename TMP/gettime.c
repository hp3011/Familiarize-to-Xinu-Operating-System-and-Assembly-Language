/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <lab0.h>

extern int getutim(unsigned long *);
extern int checksyscallsummary;

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */

	/* FIXME -- no getutim */
    unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][4].syscallName = "sys_gettime";
		syscallTable[currpid][4].syscallFreq += 1;
        endtime = ctr1000;
		syscallTable[currpid][4].syscallAvgExecTime += (endtime - starttime);
	}
    return OK;
}
