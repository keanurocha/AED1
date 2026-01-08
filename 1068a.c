#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char N[1000];

    while(fgets(N, sizeof(N), stdin) != NULL)
    {

        int verifica = 0, j = 0;

        for (char *str = N; *str != '\0'; str++)
        {
            if(*str == '(')
            {
                verifica++;
            }

            if(*str == ')')
            {
                verifica--;
                if(verifica < 0)
                {
                    j = 1;
                }
            }

        }

        if (verifica != 0 || j == 1)
        {
            printf("incorrect\n");
        }
        else
        {
            printf("correct\n");
        }
    }

}
