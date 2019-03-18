#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void do_work(unsigned int duration) {
    unsigned long start_time = (unsigned long)time(NULL);
    unsigned long end_time = start_time + duration;
    do {
        asm volatile("nop");
    } while((unsigned long)time(NULL) < end_time);
}

void main() {
    printf("start\n");
    do_work(10);
    printf("stop\n");
}