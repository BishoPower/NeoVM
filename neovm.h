#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include "utils/utils.h"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"

typedef unsigned char int8;
typedef unsigned short int16;
typedef unsigned int int32;
typedef unsigned long long int64;

#define $1 (int8 *)
#define $2 (int16 *)
#define $4 (int32 *)
#define $8 (int64 *)
#define $c (char *)
#define $i (int)

#define $ax(x) ((x)->c.r.ax)
#define $bx(x) ((x)->c.r.bx)
#define $cx(x) ((x)->c.r.cx)
#define $dx(x) ((x)->c.r.dx)
#define $sp(x) ((x)->c.r.sp)
#define $ip(x) ((x)->c.r.ip)

#define segfault(x) error((x), ErrSegv);

#define NoError 0x00
#define SysHlt 0x01
#define ErrMem 0x02
#define ErrSegv 0x04

typedef unsigned short int Reg;

struct s_registers
{
    Reg ax;
    Reg bx;
    Reg cx;
    Reg dx;
    Reg sp;
    Reg ip;
};
typedef struct s_registers Registers;

struct s_cpu
{
    Registers r;
};
typedef struct s_cpu CPU;

enum e_opcode
{
    mov = 0x01,
    nop = 0x02,
    hlt = 0x03
};
typedef enum e_opcode Opcode;

struct s_instrmap
{
    Opcode o;
    int8 s;
};
typedef struct s_instrmap IM;

typedef int16 Args;
struct s_instruction
{
    Opcode o;
    Args a[];
};
typedef struct s_instruction Instruction;

typedef unsigned char Errorcode;
typedef int8 Memory[((int16)(-1))];
typedef int8 Program;

struct s_vm
{
    CPU c;
    Memory m;
    int16 b; // break the line
};
typedef struct s_vm VM;
typedef Memory *Stack;

static IM instrmap[] = {
    {mov, 0x03},
    {nop, 0x01},
    {hlt, 0x01},
};
#define IMs (sizeof(instrmap) / sizeof(struct s_instrmap))

void __mov(VM *, Opcode, Args, Args);

void error(VM *, Errorcode);
void execinstr(VM *, Program *);
void execute(VM *);
// Example is temporary
Program *example(VM *);
int8 map(Opcode);
VM *vm_init(void);
int main(void);