#include "neovm.h"

void __mov(VM *vm, Opcode o, Args a1, Args a2)
{
    $ax(vm) = (Reg)a1;

    return;
}

void execinstr(VM *vm, Instruction i)
{
    Args a1, a2;
    int16 size;

    a1 = a2 = 0;
    size = map(i.o);
    switch (size)
    {
    case 1:
        break;

    case 2:
        a1 = i.a[0];
        break;

    case 3:
        a1 = i.a[0];
        a2 = i.a[1];
        break;

    default:
        segfault(vm);
        break;
    }

    switch (i.o)
    {
    case mov:
        __mov(vm, i.o, a1, a2);
        break;

    case nop:
        break;

    case hlt:
        error(vm, SysHlt);
        break;
    }

    return;
}

void execute(VM *vm)
{
    int32 brkaddr;
    Program *pp;
    int16 size;
    Instruction ip;

    assert(vm && *vm->m);
    size = 0;
    brkaddr = ((int32)vm->m + vm->b);
    pp = (Program *)&vm->m;

    fflush(stdout);
    do
    {
        $ip(vm) += size;
        pp += size;

        ip.o = *pp;
        if ((int32)pp > brkaddr)
            segfault(vm);
        size = map(ip.o);
        execinstr(vm, ip);
    } while (*pp != (Opcode)hlt);

    return;
}

void error(VM *vm, Errorcode e)
{
    int8 exitcode;

    exitcode = -1;
    if (vm)
        free(vm);

    switch (e)
    {
    case ErrSegv:
        fprintf(stderr, "%s\n", "VM Segmentation fault");
        break;

    case SysHlt:
        fprintf(stderr, "%s\n", "System halted");
        exitcode = 0;
        printf("ax = %.04hx\n", $i $ax(vm));

        break;

    default:
        break;
    }

    exit(exitcode);
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
    Instruction *i1, *i2, *i3;
    Args a1;
    int16 s1, s2, sa1;

    a1 = 0;
    s1 = map(mov);
    s2 = map(nop);

    i1 = (Instruction *)malloc($i s1);
    i2 = (Instruction *)malloc(s2);
    i3 = (Instruction *)malloc(s2);
    assert(i1 && i2);
    zero($1 i1, s1);
    zero($1 i2, s2);
    zero($1 i3, s2);

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

    p++;
    i3->o = hlt;
    copy($1 p, $1 i3, 1);

    vm->b = (s1 + sa1 + s2 + s2);
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

    execute(vm);

    printhex($1 prog, (map(mov) + map(nop) + map(hlt)), ' ');

    return 0;
}

#pragma GCC diagnostic pop
