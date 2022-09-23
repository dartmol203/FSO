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

    // printf("\t%d \n", param->n[i]);
    if (param->n <= 508079)
    {
        param->n = 508079;
    }
    else
    {
        if (param->n % 2 == 0)
        {
            param->n += 1;
            // printf("\t\t%d \n", param->n[i]);
        }
        double raiz = sqrt((double)param->n);
        param->result = printa(param->n, raiz);
    }
}

int main(void)
{
    int qtd, i = 0;

    scanf("%d", &qtd);

    parametro_thread PARAMETRO_A;
    parametro_thread PARAMETRO_B;
    parametro_thread PARAMETRO_C;

    pthread_t tid, tid2;
    while (qtd % 3 != 0)
    {
        scanf(" %d", &PARAMETRO_C.n);
        qtd--;
        calcula_quase_primo_maluco(&PARAMETRO_C);
        printf("%d\n", PARAMETRO_C.result);
    }
    while (qtd > 0)
    {
        scanf(" %d", &PARAMETRO_A.n);

        scanf(" %d", &PARAMETRO_B.n);

        scanf(" %d", &PARAMETRO_C.n);

        pthread_create(&tid, NULL, calcula_quase_primo_maluco, &PARAMETRO_A);
        pthread_create(&tid2, NULL, calcula_quase_primo_maluco, &PARAMETRO_B);
        calcula_quase_primo_maluco(&PARAMETRO_C);
        pthread_join(tid, NULL);
        pthread_join(tid2, NULL);

        printf("%d\n", PARAMETRO_A.result);
        printf("%d\n", PARAMETRO_B.result);
        printf("%d\n", PARAMETRO_C.result);

        qtd -= 3;
    }

    return 0;
}