#include "cpu/exec.h"

make_EHelper(jmp) {
  // the target address is calculated at the decode stage
  /*rtl_add(&t0, cpu.pc, 4);
  rtl_sr(id_dest->reg, &t0, 4);

  rtl_add(&t0, int(cpu.pc), &id_src->val);

  rtl_j(t0);*/

  print_asm_template2(jal);
}