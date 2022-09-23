#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct parametro_thread
{
    int *n;
    int tid;
    int inicio;
    int fim;
} parametro_thread;

int printa(int num, double raiz)
{
    if (num <= 508079)
    {
        return 508079;
    }
    else
    {
        int count = 0;
        if ((num & 1 != 0) && (num % 3 != 0) && (num % 5 != 0) && (num % 7 != 0))
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
        return printa(num + 1, raiz);
    }
}

void *calcula_quase_primo_maluco(void *parameter)
{
    parametro_thread *param = parameter;
    for (int i = param->inicio; i < param->fim; i++)
    {

        double raiz = sqrt((double)param->n[i]);
        param->n[i] = printa(param->n[i], raiz);
    }

    pthread_exit(NULL);
}

void calcula_quase_primo_maluco2(void *parameter)
{
    parametro_thread *param = parameter;
    for (int i = param->inicio; i < param->fim; i++)
    {

        double raiz = sqrt((double)param->n[i]);
        param->n[i] = printa(param->n[i], raiz);
    }
}

int main(void)
{
    int qtd, i = 0;

    scanf("%d", &qtd);

    parametro_thread PARAMETRO_A;
    parametro_thread PARAMETRO_B;
    parametro_thread PARAMETRO_C;

    PARAMETRO_A.n = malloc(sizeof(int) * (qtd));
    PARAMETRO_B.n = PARAMETRO_A.n;
    PARAMETRO_C.n = PARAMETRO_A.n;
    while (i != qtd)
    {
        scanf(" %d", &PARAMETRO_A.n[i]);
        i++;
        /*
        if (i != qtd)
        {
            scanf(" %d", &PARAMETRO_B.n[PARAMETRO_B.qnt++]);
            i++;
        }
        if (i != qtd)
        {
            scanf(" %d", &PARAMETRO_C.n[PARAMETRO_C.qnt++]);
            i++;
        }
        */
    }
    pthread_t tid, tid2;

    int varia = ((qtd - 0) / 3);

    PARAMETRO_A.inicio = 0 + (varia * 0);
    PARAMETRO_A.fim = 0 + (varia * 0) + varia;
    PARAMETRO_B.inicio = 0 + (varia * 1);
    PARAMETRO_B.fim = 0 + (varia * 1) + varia;
    PARAMETRO_C.inicio = 0 + (varia * 2);
    PARAMETRO_C.fim = 0 + (varia * 2) + varia + (qtd % 3);

    /*
    printf("%d %d \n", PARAMETRO_A.inicio, PARAMETRO_A.fim);
    printf("%d %d \n", PARAMETRO_B.inicio, PARAMETRO_B.fim);
    printf("%d %d \n", PARAMETRO_C.inicio, PARAMETRO_C.fim);
    */

    pthread_create(&tid, NULL, calcula_quase_primo_maluco, &PARAMETRO_A);
    pthread_create(&tid2, NULL, calcula_quase_primo_maluco, &PARAMETRO_B);
    calcula_quase_primo_maluco2(&PARAMETRO_C);
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    for (int i = 0; i < qtd; i++)
    {
        printf("%d\n", PARAMETRO_A.n[i]);
    }
    return 0;
}