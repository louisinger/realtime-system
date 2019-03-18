#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void do_work(unsigned int duration);
void signal_handler(int si_num);

int main(int argc, char* argv[]) {
    signal(SIGUSR1, signal_handler);
    pid_t pid = getpid();
    printf("process PID: %d\n", pid);
    pause();
    return 0;
}

void signal_handler(int si_num) {
    printf("received !\n");
    do_work(3);
}

void do_work(unsigned int duration) {
    unsigned long start_time = (unsigned long)time(NULL);
    unsigned long end_time = start_time + duration;
    do {
        asm volatile("nop");
    } while((unsigned long)time(NULL) < end_time);
}