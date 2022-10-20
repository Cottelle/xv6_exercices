#include "types.h"
#include "stat.h"
#include "user.h"

void child(void)
{
    printf(1, "creat\n");
    for (int i = 100000; i > 0; i--)
    {
        shc(1);
    }
    printf(1, "exxit\n");

    exit();
}

int main(void)
{
    int i;

    if (shc(-1) == -1)
    {
        printf(2, "Erreur shc\n");
        exit();
    }

    for (int j = 0; j < 4; j++)
    {
        if ((i = fork()) == -1)
        {
            printf(2, "Erreur fork\n");
            exit();
        }
        if (i == 0)
            child();
        printf(1, "pid= %d", i);
    }

    for (int j = 0; j < 4; j++)
        if (wait() == -1)
        {
            printf(2, "Erreur wait\n");
            exit();
        }
    printf(1, "Compteur = %d\n", shc(0));
    exit();
}