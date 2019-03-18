#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void do_work(unsigned int duration);
void signal_handler(int si_num);

int signal_flag = 0;

int main(int argc, char* argv[]) {
    pid_t pid = getpid();
    printf("process PID: %d\n", (int)pid);
    signal(SIGUSR1, signal_handler);
    kill(pid, SIGUSR1);

    while(1){
        sleep(1);
        kill(pid, SIGUSR1);
    }
    return 0;
}

void signal_handler(int si_num) {
    printf("signal now.\n");
    do_work(1);
}

void do_work(unsigned int duration) {
    unsigned long start_time = (unsigned long)time(NULL);
    unsigned long end_time = start_time + duration;
    do {
        asm volatile("nop");
    } while((unsigned long)time(NULL) < end_time);
}