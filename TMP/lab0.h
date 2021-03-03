extern long zfunction(long params);
extern void printsegaddress();
extern void printtos();
extern void printprocstks(int prior);
extern void syscallsummary_start(); 
extern void syscallsummary_stop();
extern void printsyscallsummary();

extern unsigned long ctr1000;
extern int currpid;
extern int process_trace[];

struct summarysyscall {
    char *syscallName;
    unsigned int syscallFreq;
    unsigned int syscallAvgExecTime;
}syscallTable[100][27];