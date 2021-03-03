/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <lab0.h>

extern int checksyscallsummary;
/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{
	STATWORD ps;    
	struct	mblock	*p, *q;
	unsigned top;
	unsigned long starttime = ctr1000;
	unsigned long endtime;
	if (checksyscallsummary == 1) {
		syscallTable[currpid][0].syscallName = "sys_freemen";
		syscallTable[currpid][0].syscallFreq += 1;
	}

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end))
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][0].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);
		if (checksyscallsummary == 1) {
			endtime = ctr1000;
			syscallTable[currpid][0].syscallAvgExecTime += (endtime - starttime);
		}
		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	if (checksyscallsummary == 1) {
		endtime = ctr1000;
		syscallTable[currpid][0].syscallAvgExecTime += (endtime - starttime);
	}
	return(OK);
}
