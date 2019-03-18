#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define PERIOD_SEC 1
#define PERIOD_NSEC 0

void *listen()
{
    printf("This is a periodic task\n");
}

int main(void)
{
    timer_t timer_id;
    struct itimerspec mytimer;

    signal(SIGALRM, (void *)listen);

    timer_create(CLOCK_REALTIME, NULL, &timer_id);

    mytimer.it_value.tv_sec = PERIOD_SEC;
    mytimer.it_value.tv_nsec = PERIOD_NSEC;

    mytimer.it_interval.tv_sec = PERIOD_SEC;
    mytimer.it_interval.tv_nsec = PERIOD_NSEC;

    timer_settime(timer_id, 0, &mytimer, NULL);

    while (1)
        pause();

    return 0;
}