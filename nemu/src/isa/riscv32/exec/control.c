#include "cpu/exec.h"

make_EHelper(jmp) {
  // the target address is calculated at the decode stage
  
  rtl_sr(id_dest->reg, &id_src2->val, 4);
  printf("0x%08x\n",decinfo.jmp_pc);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jal);
}