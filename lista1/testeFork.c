#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

    for (int i = 0; i < 4; i++)
        fork();

    printf("FSO\n");

    while (1)
    {
        /* code */
    }

    return 0;
}