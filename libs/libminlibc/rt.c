#define UARTPICO 0x20000000
#include <unistd.h>
#include <time.h> 

void   runtime_write(size_t len, char *buffer) {
    while(len--) {
        *(char *)(UARTPICO) = *buffer;
        buffer += 1;
    } 
}

void    runtime_block(unsigned long milliseconds) {}
void    runtime_exit(void) {}
int     runtime_memprotect(void *addr, size_t length, int prot) {return -1;} 
int     runtime_pagesize(void) {return -1;}
time_t  runtime_time(void){return (time_t)(-1);}
int     runtime_gettimeofday(struct timeval * tv) {return -1;}
int     runtime_rusage(int who, struct rusage * ru) {return -1;} 

 

