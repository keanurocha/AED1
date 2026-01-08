#include <stdio.h>

int main()
{
    int entrada = 0;

    scanf("%d", &entrada);

    while (entrada != 0)
    {
        int fila[100];

        int t = entrada;
        
        int pop[entrada];

        for (int i = 0; i < entrada; i++)
        {
            fila[i] = (entrada - t + 1);
            t--;
        }

        int tam = entrada;

        t = entrada;
        
        int p = 0;
        int s = 0;

        while (tam > 1)
        {
            pop[p++] = fila[s];
            s = s + 1;
            tam--;
            fila[t] = fila[s++];
            t = t + 1;
        }

        
        printf("Discarded cards: ");

        for (int i = 0; i < (entrada - 1); i++)
        {
            if (i == entrada - 2)
            {
                printf("%d", pop[i]);
                break;

            }
            printf("%d, ", pop[i]);
        }

        printf("\nRemaining card: %d\n", fila[s]);

        scanf("%d", &entrada);
    }
 
}
