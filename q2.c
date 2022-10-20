
#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "resource.h"

#define MILLION (1000 * 1000)
/* / / Programme pour tester le fonctionnement de getrusage.
//
/ / Prend 3 arguments entiers :
/ / - nombre d’itérations pour consommer du temps en mode utilisateur
/ / - nombre d’itérations pour consommer du temps en mode système
/ / - nombre de pages a allouer
//
/ / Exemple :
/ / > q2 1 1 0 (test cpu user + cpu sys)
/ / user=65, sys=123, maxrss=5
/ / > q2 0 0 3 (test maxrss)
/ / user=0, sys=0, maxrss=8
/ / > q2 10 5 17 (la totale)18
Chapitre 5 - Ordonnancement
/ / user=752, sys=610, maxrss=22 */
int cpuuser(void) // passe du temps en mode utilisateur
{
    int s = 0;
    for (int i = 0; i < 100 * MILLION; i++)
    {
        if (!(i % 100000))
            s += i;                         //Ne passe pas l'a opti du compil ?????
    }
    return s;
}
void cpusys(void)
{
    int fd;
    char c;
    // passe du temps en mode systeme
    fd = open("README", O_RDONLY);
    if (fd == -1)
    {
        printf(2, " cannot  open  README \n ");
        exit();
    }
    while (read(fd, &c, 1) > 0)
        ;
    close(fd);
}
void consomme(int npages, int nuser, int nsys)
{
    int i, s;
    if (sbrk(npages * 4096) == 0)
    {
        printf(2, " cannot sbrk %d pages \n ", npages);
        return;
    }
    s = 0;
    for (i = 0; i < nuser; i++)
        s += cpuuser();
    for (i = 0; i < nsys; i++)
        cpusys();
    exit();
}
int main(int argc, char *argv[])
{
    int npages, nuser, nsys;
    // int status;
    struct rusage u;
    if (argc != 4)
    {
        printf(2, " usage :  %s  nuser  nsys  npages \n ", argv[0]);
        exit();
    }
    nuser = atoi(argv[1]);
    nsys = atoi(argv[2]);
    npages = atoi(argv[3]);
    switch (fork())
    {
    case -1:
        printf(2, " cannot  fork \n ");
        exit();
    case 0:
        consomme(npages, nuser, nsys);
        exit();
    default:
        if (wait() == -1)
        {
            printf(2, " cannot  wait \n ");
            exit();
        }
        // printf(1, "exit(%d)\", status);
        if (getrusage(&u) == -1)
            printf(2, " cannot  rusage \n ");
        printf(1, " user =%d ,  sys =%d ,  maxrss =%d \n ", u.ru_utime, u.ru_stime, u.ru_maxrss);
    }
    exit();
}