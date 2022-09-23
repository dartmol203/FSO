
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct parametro_thread
{
    int n;
    int result;
} parametro_thread;

int ehquaseprimo(int num, float raiz)
{
    if (num % 2 == 0)
        return 0;

    int cnt = 0;
    for (int i = 3; i < raiz; i += 2)
    {
        if (num % i == 0 && i < 11)
            return 0;
        if (num % i == 0 && i > 10)
            cnt++;
        if (cnt >= 10)
            return 1;
    }

    return 0;
}

void *quaseprimo(void *arg)
{
    parametro_thread *param = arg;
    int num = (param->n) + 1;

    if (num <= 508079)
        param->result = 508079;
    else
    {
        while (1)
        {
            if (ehquaseprimo(num, floor(sqrt(num))))
            {
                param->result = num;
                break;
            }
            num++;
        }
    }
}

int main(void)
{
    int qtd;

    scanf("%d", &qtd);

    parametro_thread PARAMETRO[3];

    pthread_t tid[2];

    while (qtd > 0)
    {
        if (qtd >= 3)
        {

            if ((scanf(" %d", &PARAMETRO[0].n)) == EOF)
            {
                break;
            }

            pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
            pthread_join(tid[0], NULL);
            printf("%d\n", PARAMETRO[0].result);

            if ((scanf(" %d", &PARAMETRO[1].n)) == EOF)
            {
                break;
            }

            pthread_create(&tid[1], NULL, quaseprimo, &PARAMETRO[1]);
            pthread_join(tid[1], NULL);
            printf("%d\n", PARAMETRO[1].result);

            if ((scanf(" %d", &PARAMETRO[2].n)) == EOF)
            {
                break;
            }

            quaseprimo(&PARAMETRO[2]);
            printf("%d\n", PARAMETRO[2].result);
            qtd -= 3;
        }
        else if (qtd == 2)
        {
            if ((scanf(" %d", &PARAMETRO[0].n)) == EOF)
            {
                break;
            }

            pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
            pthread_join(tid[0], NULL);
            printf("%d\n", PARAMETRO[0].result);

            if ((scanf(" %d", &PARAMETRO[1].n)) == EOF)
            {
                break;
            }

            pthread_create(&tid[1], NULL, quaseprimo, &PARAMETRO[1]);
            pthread_join(tid[1], NULL);
            printf("%d\n", PARAMETRO[1].result);

            qtd -= 2;
        }
        else
        {
            if ((scanf(" %d", &PARAMETRO[0].n)) == EOF)
            {
                break;
            }

            pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
            pthread_join(tid[0], NULL);
            printf("%d\n", PARAMETRO[0].result);
            qtd--;
        }
    }
    return 0;
}
