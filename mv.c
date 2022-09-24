// #include <unistd.h>
// #include <stdio.h>
// #include <errno.h>
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf(2, "Usage mv old_name new_name\n");
        exit();
    }
    if (link(argv[1], argv[2]) <0)
    {
        printf(2, "Erreur link\n");
        exit();
    }
    if (unlink(argv[1]) <0)
        printf(2, "Erreur unlink\n");
    exit();
}