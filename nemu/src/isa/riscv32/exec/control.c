#include "cpu/exec.h"

make_EHelper(jal) {
  // the target address is calculated at the decode stage
  
  rtl_sr(id_dest->reg, &id_src2->val, 4);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jal);
}

make_EHelper(jalr) {

  t0 = decinfo.seq_pc;
  decinfo.jmp_pc = (reg_l(id_src->reg) + id_src2->val) & ~1;
  rtl_sr(id_dest->reg, &t0, 4);
  rtl_j(decinfo.jmp_pc);

  difftest_skip_dut(1, 2);

  print_asm_template2(jalr);
}

make_EHelper(relop) {

  if(decinfo.opcode==0){
      rtl_jrelop(RELOP_EQ, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(beq);
  }
  else if(decinfo.opcode==1){
      rtl_jrelop(RELOP_NE, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(bne);
  }
  else if(decinfo.opcode==4){
      rtl_jrelop(RELOP_LT, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(bne);
  }
  else if(decinfo.opcode==5){
      rtl_jrelop(RELOP_GE, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(bne);
  }
  else if(decinfo.opcode==6){
      rtl_jrelop(RELOP_LTU, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(bne);
  }
  else if(decinfo.opcode==7){
      rtl_jrelop(RELOP_GEU, &id_src->val, &id_src2->val, decinfo.jmp_pc);
      print_asm_template2(bne);
  }
  else{
    printf("%08x %d\n",cpu.pc,decinfo.opcode);
    assert(0);
  }
}