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
    parametro_thread Parametro_A;
    parametro_thread Parametro_B;
    parametro_thread Parametro_C;
    pthread_t tid;
    pthread_t tid2;

    scanf("%d", &qtd);

    while (qtd > 0)
    {
        if (qtd >= 3)
        {
            scanf("%d", &Parametro_A.n);
            pthread_create(&tid, NULL, quaseprimo, &Parametro_A);

            scanf("%d", &Parametro_B.n);
            pthread_create(&tid2, NULL, quaseprimo, &Parametro_B);

            scanf("%d", &Parametro_C.n);
            quaseprimo(&Parametro_C);

            pthread_join(tid, NULL);
            pthread_join(tid2, NULL);

            printf("%d\n", Parametro_A.result);
            printf("%d\n", Parametro_B.result);
            printf("%d\n", Parametro_C.result);
            qtd -= 3;
        }
        else if (qtd == 2)
        {
            scanf("%d", &Parametro_A.n);
            pthread_create(&tid, NULL, quaseprimo, &Parametro_A);

            scanf("%d", &Parametro_C.n);
            quaseprimo(&Parametro_C);

            pthread_join(tid, NULL);
            printf("%d\n", Parametro_A.result);
            printf("%d\n", Parametro_C.result);

            qtd -= 2;
        }
        else if (qtd < 2)
        {
            scanf("%d", &Parametro_C.n);
            quaseprimo(&Parametro_C);
            printf("%d\n", Parametro_C.result);
            qtd--;
        }
    }

    return 0;
}
