#include "cpu/exec.h"

make_EHelper(lui);
make_EHelper(add);
make_EHelper(auipc);

make_EHelper(ld);
make_EHelper(st);

make_EHelper(inv);
make_EHelper(nemu_trap);

make_EHelper(jmp);
make_EHelper(jalr);
make_EHelper(beq);
