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

void *verificaProxQuaseprimo(void *parametro)
{
    parametro_thread *param = parametro;
    int num = (param->n) + 1;

    if (num <= 508079)
        param->result = 508079;
    else
    {
        if (num % 2 == 0)
        {
            num++;
        }
        while (1)
        {
            if (ehquaseprimo(num, floor(sqrt(num))))
            {
                param->result = num;
                return;
            }
            num++;
        }
    }
    return NULL;
}

int main(void)
{
    int qtd;

    scanf("%d", &qtd);

    parametro_thread param1, param2, param3;

    pthread_t tid1, tid2;

    while (qtd > 0)
    {
        if (qtd >= 3)
        {

            scanf(" %d", &param1.n);

            pthread_create(&tid1, NULL, verificaProxQuaseprimo, &param1);
            pthread_join(tid1, NULL);
            printf("%d\n", param1.result);

            scanf(" %d", &param2.n);

            pthread_create(&tid2, NULL, verificaProxQuaseprimo, &param2);
            pthread_join(tid2, NULL);
            printf("%d\n", param2.result);

            scanf(" %d", &param3.n);

            verificaProxQuaseprimo(&param3);
            printf("%d\n", param3.result);
            qtd -= 3;
        }
        else if (qtd == 2)
        {
            scanf(" %d", &param1.n);

            pthread_create(&tid1, NULL, verificaProxQuaseprimo, &param1);
            pthread_join(tid1, NULL);
            printf("%d\n", param1.result);

            scanf(" %d", &param3.n);

            verificaProxQuaseprimo(&param3);
            printf("%d\n", param3.result);

            qtd -= 2;
        }
        else
        {
            scanf(" %d", &param3.n);

            verificaProxQuaseprimo(&param3);
            printf("%d\n", param3.result);
            qtd--;
        }
    }
    return 0;
}
