#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int tam;

#define LESS(A, B) (A < B)
#define EXCH(A, B) \
    {              \
        int t = B; \
        B = A;     \
        A = t;     \
    }
#define CMPEXCH(A, B)   \
    {                   \
        if (LESS(B, A)) \
            EXCH(A, B); \
    }

int separa(int *v, int l, int r)
{
    int c = v[r]; // pivô
    int t, j = l;
    for (int k = l; /*A*/ k < r; ++k)
        if (v[k] <= c)
        {
            t = v[j], v[j] = v[k], v[k] = t;
            ++j;
        }
    t = v[j], v[j] = v[r], v[r] = t;
    return j;
}

void quickSort(int *v, int l, int r)
{
    if (r <= l)
        return;

    CMPEXCH(v[(l + r) / 2], v[r]);
    CMPEXCH(v[l], v[(l + r) / 2]);
    CMPEXCH(v[r], v[(l + r) / 2]);

    int j = separa(v, l, r);
    quickSort(v, l, j - 1);
    quickSort(v, j + 1, r);
}

void *ordena(void *args)
{
    quickSort((int *)args, 0, tam - 1);
    return;
}

int main()
{

    int *v1, *v2;
    int flag = 0, saida;
    pthread_t t1, t2;
    saida = scanf(" %d", &tam);

    v1 = malloc(sizeof(int) * tam);
    v2 = malloc(sizeof(int) * tam);

    for (int i = 0; i < tam; i++)
        saida = scanf(" %d", &v1[i]);

    for (int i = 0; i < tam; i++)
        saida = scanf(" %d", &v2[i]);

    saida = pthread_create(&t1, NULL, ordena, (void *)v1);
    saida = pthread_create(&t2, NULL, ordena, (void *)v2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for (int i = 0; i < tam; i++)
    {
        if (v1[i] != v2[i])
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Mesmos elementos\n");
    }
    else
    {
        printf("Diferentes\n");
    }

    return 0;
}