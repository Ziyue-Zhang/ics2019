#include "cpu/exec.h"

make_EHelper(jal) {
  // the target address is calculated at the decode stage
  
  rtl_sr(id_dest->reg, &id_src2->val, 4);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jal);
}

make_EHelper(jalr) {

  t0 = decinfo.seq_pc + 4;
  decinfo.jmp_pc = (reg_l(id_src->reg) + id_src2->val) & ~1;
  rtl_sr(id_dest->reg, &t0, 4);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jalr);
}

make_EHelper(relop) {
  // the target address is calculated at the decode stage
  if(decinfo.opcode==0){
      rtl_jrelop(RELOP_EQ, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(beq);
  }
  else if(decinfo.opcode==1){
    printf("%08x\n",cpu.pc);
      printf("%08x\n",decinfo.jmp_pc);
      rtl_jrelop(RELOP_NE, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(bne);
  }
  else{
    printf("%d\n",decinfo.opcode);
    assert(0);
  }
}