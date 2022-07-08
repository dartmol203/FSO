#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void trataSinal(int sig)
{
}

int main()
{
    signal(SIGUSR1, trataSinal);
    signal(SIGUSR2, trataSinal);

    pause();

    if (fork() == 0)
    {
        exit(0);
    }
    pause();
    wait(NULL);
    pause();
    exit(0);
}