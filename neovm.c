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

Program example()
{
    int16 size;
    Instruction i1, i2;

    size = map(mov);
    i1 = (Instruction)malloc($i size);
    if (!i1)
    {
        errno = ErrMem;
        return (Program)0;
    }

    size = map(nop);
    i2 = (Instruction)malloc($i size);
    if (!i2)
    {
        errno = ErrMem;
        return (Program)0;
    }

    Program prog = {i1, i2};
    // copy(prog, (Instruction *[]){i1, i2}, sizeof(prog));

    return prog;
}

Program *example()
{
    Program *prog;
    Instruction *i1, *i2;
    Args *a1;
    int16 s1, s2, sa1, ps;

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
    {
        a1 = (Args *)malloc($i sa1);
        assert(a1);
        zero(a1, sa1);
        *a1 = 0x00;
        *(a1 + 1) = 0x05;
    }

    ps = (s1 + s2);
    prog = (Program *)malloc($i ps);
}

int main(int argc, char *argv[])
{
    int8 size;
    Program *prog;
    VM *vm;

    size = (map(mov) + map(nop));
    prog = example();
    printf("prog = %p\n", prog);

    vm = vm_init(prog, size);
    printf("vm = %p\n", vm);

    return 0;
}

#pragma GCC diagnostic pop
