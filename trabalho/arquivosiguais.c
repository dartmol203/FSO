#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    unsigned int saida1, saida2;
    FILE *f1, *f2;
    char *cont1, *cont2;
    int flag = 0;
    cont1 = malloc(sizeof(char) * 300 * 1000000);
    cont2 = malloc(sizeof(char) * 300 * 1000000);
    for (int i = 1; i < argc; i++)
    {
        f1 = fopen(argv[i], "rb");
        saida1 = fread(cont1, sizeof(char), 300 * 1000000, f1);
        for (int j = i + 1; j < argc; j++)
        {
            f2 = fopen(argv[j], "rb");
            saida2 = fread(cont2, sizeof(char), 300 * 1000000, f2);
            printf("%s %s ", argv[i], argv[j]);

            if (saida1 != saida2)
            {
                printf("diferentes\n");
            }
            else
            {
                flag = 0;
                for (int k = 0; k < saida1; k++)
                {
                    if (cont1[k] != cont2[k])
                    {
                        printf("diferentes\n");
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("iguais\n");
                }
            }
            fclose(f2);
        }
        fclose(f1);
    }

    return 0;
}
