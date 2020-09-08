#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(add) {

  if(decinfo.opcode==0){
      rtl_add(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(add);
  }
  else if(decinfo.opcode==7){
      rtl_and(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(add);
  }
  else{
    assert(0);
  }
}

make_EHelper(compute) {

  if(decinfo.opcode==0){
      if(decinfo.isa.instr.funct3==0){
          rtl_add(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(add);
      }
      else if(decinfo.isa.instr.funct3==2){
          if((int)id_src->val<(int)id_src2->val){
            t0=1;
          }
          else{
            t0=0;
          }
          rtl_sr(id_dest->reg, &t0, 4);

          print_asm_template2(add);
      }
      else{
        assert(0);
      }
  }
  else if(decinfo.opcode==32){
      rtl_sub(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(sub);
  }
  else if(decinfo.opcode==1){
      rtl_imul_lo(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(sub);
  }
  else{
      printf("%08x %d\n",cpu.pc,decinfo.opcode);
      assert(0);
  }
}

make_EHelper(auipc) {

  t0 = cpu.pc;

  rtl_add(&id_dest->val, &id_src->val, &t0);
  rtl_sr(id_dest->reg, &id_dest->val, 4);

  print_asm_template2(add);
}