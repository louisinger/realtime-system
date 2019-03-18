#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define PROCESS_VAR 400000000
#define PERIOD_SEC 1
#define PERIOD_NSEC 0

int t = 0;

void do_work(unsigned int duration)
{
for (int i = 0; i < PROCESS_VAR * duration; i++)
{
asm volatile("nop");
}
printf("\ndo work terminated\n");
}

void* t2() {
    printf("function t2\n");
}

void* t3() {
    printf("function t3\n");
}

void* t4() {
    printf("function t4\n");
}

void* signal_handler(int sino) {
    t++;
}

int main(void) {
    timer_t timer_id;
    struct itimerspec mytimer;

    signal(SIGALRM, (void *)signal_handler);

    timer_create(CLOCK_REALTIME, NULL, &timer_id);

    mytimer.it_value.tv_sec = PERIOD_SEC;
    mytimer.it_value.tv_nsec = PERIOD_NSEC;

    mytimer.it_interval.tv_sec = PERIOD_SEC;
    mytimer.it_interval.tv_nsec = PERIOD_NSEC;

    timer_settime(timer_id, 0, &mytimer, NULL);

    while(1){
        pause();
        printf("t = %d\n", t);
        if(t%2 == 0) {
            t2();
        } else if(t%3 == 0) {
            t3();
        } else if(t%4 == 0) {
            t4();
        }
    }
}
