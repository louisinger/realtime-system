#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void do_work(unsigned int duration);
void signal_handler();
void signal_received(int si_num);

int signal_handled = 0;
int run = 1;

int main(int argc, char* argv[]) {
    pid_t pid = getpid();
    printf("process PID: %d", (int)pid);
    signal(SIGUSR1, signal_received);

    while(run == 1) {
        asm volatile("nop");
        signal_handler();
    }

    return 0;
}

void signal_received(int si_num) {
    printf("I have received the signal: %d", si_num);
    signal_handled++;
}

void signal_handler() {
    if(signal_handled > 0) {
        do_work(3);
        signal_handled--;
    }
}

void do_work(unsigned int duration) {
    unsigned long start_time = (unsigned long)time(NULL);
    unsigned long end_time = start_time + duration;
    do {
        asm volatile("nop");
    } while((unsigned long)time(NULL) < end_time);
}