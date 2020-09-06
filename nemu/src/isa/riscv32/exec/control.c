#include "cpu/exec.h"

make_EHelper(jmp) {
  // the target address is calculated at the decode stage
  
  rtl_sr(id_dest->reg, &id_src2->val, 4);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jal);
}

make_EHelper(jalr) {
  // the target address is calculated at the decode stage
  printf("nmsl");
  /*t0 = cpu.pc + 4;
  //cpu.pc = 
  rtl_sr(id_dest->reg, &id_src2->val, 4);
  rtl_j(decinfo.jmp_pc);*/

  print_asm_template2(jalr);
}