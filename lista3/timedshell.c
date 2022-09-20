#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

// Time Inicio
struct timeval inicio, overall_start, overall_end;
int error = 0, flag = 0;

int main()
{
    // Recebe PATH
    char PATH[256], arg[256];
    while (scanf("%s %s", PATH, arg) != EOF)
    {
        // Flag e time
        if (flag == 0)
        {
            gettimeofday(&overall_start, NULL);
            flag++;
        }
        gettimeofday(&inicio, NULL);

        // Cria fork
        fflush(stdout);
        int pid = fork();

        // Se for o filho
        if (pid == 0)
        {
            execl(PATH, PATH, arg, NULL);
            if (strcmp(strerror(errno), "Success") != 0)
            {
                printf("> Erro: %s\n", strerror(errno));
                fflush(stdout);
                error = errno;
                fclose(stdin);
                exit(errno);
            }
        }
        if (waitpid(pid, &error, WUNTRACED))
        {
            error = WEXITSTATUS(error);
            struct timeval final;
            gettimeofday(&final, NULL);
            printf("> Demorou %.1lf segundos, retornou %d\n", (double)(final.tv_usec - inicio.tv_usec) / 1000000 + (double)(final.tv_sec - inicio.tv_sec), error);
            fflush(stdout);
        }
    }
    gettimeofday(&overall_end, NULL);

    printf(">> O tempo total foi de %.1lf segundos\n", (double)(overall_end.tv_usec - overall_start.tv_usec) / 1000000 + (double)(overall_end.tv_sec - overall_start.tv_sec));
    fflush(stdout);
    exit(0);
}