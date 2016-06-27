#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const int TIME = 10;

void sig_handler(int signo, siginfo_t *siginfo, void *context) {
    pid_t sender_pid = siginfo->si_pid;

    if (signo == SIGUSR1 || signo == SIGUSR2) {
        printf("%s from %d\n", (signo == SIGUSR1 ? "SIGUSR1" : (signo == SIGUSR2 ? "SIGUSR2" : "")), (int)sender_pid);
        exit(signo);
    }
}

int main() {
    struct sigaction sigact;
    sigact.sa_sigaction = *sig_handler;
    sigact.sa_flags |= SA_SIGINFO;

    sigset_t block_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGUSR1);
    sigaddset(&block_mask, SIGUSR2);
    sigact.sa_mask = block_mask;

    if (sigaction(SIGUSR1, &sigact, NULL) != 0) {
        printf("error\n");
        return errno;
    }
    if (sigaction(SIGUSR2, &sigact, NULL) != 0) {
        printf("error\n");
        return errno;
    }
    sleep(TIME);
    printf("No signals were caught\n");
    return 0;
}
