#include "neovm.h"

int8 map(Opcode o)
{
    int8 n, ret;
    IM *p;

    ret = 0;
    for (n = IMs, p = instrmap; n; n--, p++)
    {
        if (p->o == o)
        {
            ret = p->s;
            break;
        }
    }

    return ret;
}

VM *vm_init(Program *pr, int16 progsz)
{
    VM *p;
    Program *pp;
    int16 size;

    assert((pr) && (progsz > 0));
    size = (int16)sizeof(struct s_vm);
    p = (VM *)malloc($i size);
    if (p == NULL)
    {
        errno = ErrMem;
        return (VM *)0;
    }

    zero($1 p, size);
    pp = (Program *)malloc($i progsz);
    if (pp == NULL)
    {
        free(p);
        errno = ErrMem;
        return (VM *)0;
    }
    copy(pp, pr, progsz);

    return p;
}



int main(int argc, char *argv[])
{
    int8 size;
    Program prog;
    VM *vm;

    size = (map(mov) + map(nop));
    prog = example();
    printf("prog = %p\n", prog);

    vm = vm_init(prog, size);
    printf("vm = %p\n", vm);

    return 0;
}

#pragma GCC diagnostic pop
