#include "neovm.h"

void execinstr(VM *vm, Instruction *ip)
{
    Args *a1, *a2;
    int16 size;

    size = map(ip->o);
}

void execute(VM *vm)
{
    Program *pp;
    int16 size;
    Instruction *ip;

    assert(vm && vm->m);
    pp = vm->m;

    while ((*pp != (Opcode)hlt) && (pp <= (Program *)vm->b))
    {
        ip = (Instruction *)pp;
        size = map(ip->o);
        execinstr(vm, ip);

        $ip(vm) += size;
        pp += size;
    }
    if (pp > (Program *)vm->b)
        segfault(vm);
}

void error(VM *vm, Errorcode e)
{
    if (vm)
        free(vm);

    switch (e)
    {
    case ErrSegv:
        fprintf(stderr, "%s\n", "Segmentation fault");
        break;
    default:
        break;
    }

    exit(-1);
}

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
    Args a1;
    int16 s1, s2, sa1;

    a1 = 0;
    s1 = map(mov);
    s2 = map(nop);

    i1 = (Instruction *)malloc($i s1);
    i2 = (Instruction *)malloc($i s2);
    assert(i1 && i2);
    zero($1 i1, s1);
    zero($1 i2, s2);

    i1->o = mov;
    sa1 = (s1 - 1);
    a1 = 0x0005;

    p = vm->m;
    copy($1 p, $1 i1, 1);
    p += 1;

    if (a1)
    {
        copy($1 p, $1 & a1, sa1);
        p += sa1;
    }

    i2->o = nop;
    copy($1 p, $1 i2, 1);

    vm->b = (int16)(s1 + sa1 + s2);
    $ip(vm) = (Reg)vm->m;
    $sp(vm) = (Reg)-1;
    free(i1);
    free(i2);

    return (Program *)&vm->m;
}

int main()
{
    Program *prog;
    VM *vm;

    vm = vm_init();
    printf("vm = %p (sz: %zu)\n", vm, sizeof(struct s_vm)); // Change %d to %zu

    prog = example(vm);
    printf("prog = %p\n", prog);

    printhex($1 prog, (map(mov) + map(nop)), ' ');

    return 0;
}

#pragma GCC diagnostic pop
