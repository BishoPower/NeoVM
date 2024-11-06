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

VM *vm_init()
{
    VM *p;
    // Program *pp;
    int16 size;

    size = (int16)sizeof(struct s_vm);
    p = (VM *)malloc($i size);
    if (p == NULL)
    {
        errno = ErrMem;
        return (VM *)0;
    }
    zero($1 p, size);

    // pp = (Program *)malloc($i progsz);
    // if (pp == NULL)
    // {
    //     free(p);
    //     errno = ErrMem;
    //     return (VM *)0;
    // }
    // copy(pp, pr, progsz);

    return p;
}

Program *example(VM *vm)
{
    Program *p;
    Instruction *i1, *i2;
    Args *a1;
    int16 s1, s2, sa1;

    s1 = map(mov);
    s2 = map(nop);

    i1 = (Instruction *)malloc($i s1);
    i2 = (Instruction *)malloc($i s2);
    assert(i1 && i2);
    zero($1 i1, s1);
    zero($1 i2, s2);

    i1->o = mov;
    sa1 = (s1 - 1);

    if (s1)
        a1 = (Args *)malloc($i sa1);
    if (a1)
    {
        assert(a1);
        zero(a1, sa1);
        *a1 = 0x00;
        *(a1 + 1) = 0x05;
    }

    p = vm->m;
    copy($1 p, $1 i1, s1);
    p += s1;

    if (sa1)
    {
        copy($1 p, $1 a1, sa1);
        p += sa1;
        free(a1);
    }

    i2->o = nop;
    copy($1 p, $1 i2, s2);
    free(i1);
    free(i2);

    return vm->m;
}

int main()
{
    Program *prog;
    VM *vm;

    vm = vm_init();
    printf("vm = %p\n", vm);

    prog = example(vm);
    printf("prog = %p\n", prog);

    return 0;
}

#pragma GCC diagnostic pop
