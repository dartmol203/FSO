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
/*
int printa(int num, double raiz)
{
    while (1)
    {

        int count = 0;
        if ((num % 3 != 0) && (num % 5 != 0) && (num % 7 != 0))
        {
            for (int i = 11; i < raiz; i++)
            {
                if (num % i == 0)
                    count++;
            }
            if (count > 10)
            {
                return num;
            }
        }
        num += 2;
    }
}

void *calcula_quase_primo_maluco(void *parameter)
{
    parametro_thread *param = parameter;

    if (param->n <= 508079)
    {
        param->result = 508079;
    }
    else
    {
        if (param->n % 2 == 0)
        {
            param->n += 1;
        }
        double raiz = sqrt((double)param->n);
        param->result = printa(param->n, raiz);
    }
}
*/

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
    /*
    while (1)
    {
        if (scanf(" %d", &PARAMETRO[0].n) == EOF)
        {
            break;
        }
        pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
        pthread_join(tid[0], NULL);
        printf("%d\n", PARAMETRO[0].result);

        if (scanf(" %d", &PARAMETRO[1].n) == EOF)
        {
            break;
        }

        pthread_create(&tid[1], NULL, quaseprimo, &PARAMETRO[1]);
        pthread_join(tid[1], NULL);
        printf("%d\n", PARAMETRO[1].result);

        if (scanf(" %d", &PARAMETRO[2].n) == EOF)
        {
            break;
        }

        quaseprimo(&PARAMETRO[2]);
        printf("%d\n", PARAMETRO[2].result);
    }
    */

    while (qtd > 0)
    {
        if (qtd >= 3)
        {

            scanf(" %d", &PARAMETRO[0].n);

            pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
            pthread_join(tid[0], NULL);
            printf("%d\n", PARAMETRO[0].result);

            scanf(" %d", &PARAMETRO[1].n);

            pthread_create(&tid[1], NULL, quaseprimo, &PARAMETRO[1]);
            pthread_join(tid[1], NULL);
            printf("%d\n", PARAMETRO[1].result);

            scanf(" %d", &PARAMETRO[2].n);

            quaseprimo(&PARAMETRO[2]);
            printf("%d\n", PARAMETRO[2].result);
            qtd -= 3;
        }
        else if (qtd == 2)
        {
            scanf(" %d", &PARAMETRO[0].n);

            pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
            pthread_join(tid[0], NULL);
            printf("%d\n", PARAMETRO[0].result);

            scanf(" %d", &PARAMETRO[1].n);

            pthread_create(&tid[1], NULL, quaseprimo, &PARAMETRO[1]);
            pthread_join(tid[1], NULL);
            printf("%d\n", PARAMETRO[1].result);

            qtd -= 2;
        }
        else
        {
            scanf(" %d", &PARAMETRO[0].n);

            pthread_create(&tid[0], NULL, quaseprimo, &PARAMETRO[0]);
            pthread_join(tid[0], NULL);
            printf("%d\n", PARAMETRO[0].result);
            qtd--;
        }
    }
    return 0;
}
