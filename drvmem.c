#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

// static struct
// {
//     struct spinlock lock;
//     int locking;
// } drv;

// extern pde_t *walkpgdir(pde_t *pgdir, const void *va, int alloc);

int drvmemread(struct inode *ip, char *dst, int n, unsigned int off)
{
    switch (ip->minor)
    {
    case 0:
        return 0;

    case 1:
        for (int i = 0; i < n; i++)
            dst[i] = 0;
        return n;

    case 2:
        // unsigned int = of = ip->
        // struct proc *p = myproc();
        // pde_t *pde_t,*pgdir = p->pgdir;
        cprintf("\n okici %d %d %d\n",off,PHYSTOP,EXTMEM);

        if (off+n>PHYSTOP ||off<EXTMEM)
            return -1;

        memmove(dst,(char *)P2V(off),n);

        return n;
        




    default:
        return -1;
    }
}

int drvmemwrite(struct inode *ip, char *buf, int n, unsigned int off)
{
    return n;
}

void drvmeminit(void)
{
    devsw[DEVNULL].write = drvmemwrite;
    devsw[DEVNULL].read = drvmemread;
}