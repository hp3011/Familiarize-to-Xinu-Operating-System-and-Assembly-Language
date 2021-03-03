/*printsegaddress.c - printsegaddress*/
#include <stdio.h>
#include <lab0.h>

extern long etext, edata, end;

void printsegaddress()
{
	long *ptr_etext = &etext;
	long *ptr_edata = &edata;
	long *ptr_end = &end;
	
	kprintf("\nvoid printsegaddress()\n");
	kprintf("Current: etext[0x%08x]=0x%08x, edata[0x%08x]=0x%08x, ebss[0x%08x]=0x%08x\n",ptr_etext,*(ptr_etext),ptr_edata,*(ptr_edata),ptr_end,*(ptr_end));
	kprintf("Preceding: etext[0x%08x]=0x%08x, edata[0x%08x]=0x%08x, ebss[0x%08x]=0x%08x\n",(ptr_etext-1),*(ptr_etext-1),(ptr_edata-1),*(ptr_edata-1),(ptr_end-1),*(ptr_end-1));
	kprintf("After: etext[0x%08x]=0x%08x, edata[0x%08x]=0x%08x, ebss[0x%08x]=0x%08x\n",(ptr_etext+1),*(ptr_etext+1),(ptr_edata+1),*(ptr_edata+1),(ptr_end+1),*(ptr_end+1));


}
