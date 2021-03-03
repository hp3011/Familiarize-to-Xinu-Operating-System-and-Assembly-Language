
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>



int checksyscallsummary = 0;

void syscallsummary_start(){
    checksyscallsummary = 1;
}

void syscallsummary_stop(){
    checksyscallsummary = 0;
}

void printsyscallsummary(){
    kprintf("\nvoid printsyscallsummary()\n");
    int process, sys_calls, flag;
    for(process = 1; process < NPROC; process++) {
        flag = 0;
		if(process_trace[process] == 1) {
            for(sys_calls = 0; sys_calls < 27; sys_calls++) {
				if(syscallTable[process][sys_calls].syscallFreq > 0) {
					flag = 1;
				}
			}
            if (flag == 0){
				continue;
			}
            kprintf("\nProcess [pid:%d]", process);
			for(sys_calls = 0; sys_calls < 27; sys_calls++) {
				if(syscallTable[process][sys_calls].syscallFreq > 0) {
					kprintf("\n\t\tsyscall: %s, count: %d, average execution time: %lu (ms)", syscallTable[process][sys_calls].syscallName, syscallTable[process][sys_calls].syscallFreq, (syscallTable[process][sys_calls].syscallAvgExecTime/syscallTable[process][sys_calls].syscallFreq));
				}
			}
		}
	}

}