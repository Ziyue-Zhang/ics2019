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
  t0 = decinfo.seq_pc + 4;
  decinfo.jmp_pc = (reg_l(id_src->reg) + id_src2->val) & ~1;
  printf("%08x",cpu.pc);
  rtl_sr(id_dest->reg, &t0, 4);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jalr);
}