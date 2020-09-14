#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(add) {

  if(decinfo.opcode==0){
      rtl_add(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(addi);
  }
  else if(decinfo.opcode==1){
      t0 = id_src2->val & 0b111111;
      rtl_shl(&id_dest->val, &id_src->val, &t0);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(slli);
  }
  else if(decinfo.opcode==3){
      if((uint32_t)id_src->val<(uint32_t)id_src2->val){
          t0=1;
      }
      else{
          t0=0;
      }
      rtl_sr(id_dest->reg, &t0, 4);
      print_asm_template2(sltiu);
  }
  else if(decinfo.opcode==4){
      rtl_xor(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(xori);
  }
  else if(decinfo.opcode==5){
      if(decinfo.isa.instr.funct7==32){
          t0 = id_src2->val & 0b111111;
          rtl_sar(&id_dest->val, &id_src->val, &t0);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(srai);
      }
      else{
          t0 = id_src2->val & 0b111111;
          rtl_shr(&id_dest->val, &id_src->val, &t0);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(srli);
      }
  }
  else if(decinfo.opcode==6){
      rtl_or(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(ori);
  }
  else if(decinfo.opcode==7){
      rtl_and(&id_dest->val, &id_src->val, &id_src2->val);
      rtl_sr(id_dest->reg, &id_dest->val, 4);

      print_asm_template2(andi);
  }
  else{
    printf("%08x\n",cpu.pc);
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
      else if(decinfo.isa.instr.funct3==1){
          t0 = id_src2->val & 0b11111;
          rtl_shl(&id_dest->val, &id_src->val, &t0);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(sll);
      }
      else if(decinfo.isa.instr.funct3==2){
          if((int32_t)id_src->val<(int32_t)id_src2->val){
            t0=1;
          }
          else{
            t0=0;
          }
          rtl_sr(id_dest->reg, &t0, 4);

          print_asm_template2(slt);
      }
      else if(decinfo.isa.instr.funct3==3){
          if((uint32_t)id_src->val<(uint32_t)id_src2->val){
            t0=1;
          }
          else{
            t0=0;
          }
          rtl_sr(id_dest->reg, &t0, 4);

          print_asm_template2(sltu);
      }
      else if(decinfo.isa.instr.funct3==4){
          rtl_xor(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(xor);
      }
      else if(decinfo.isa.instr.funct3==5){
          t0 = id_src2->val & 0b11111;
          rtl_shr(&id_dest->val, &id_src->val, &t0);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(sll);
      }
      else if(decinfo.isa.instr.funct3==6){
          rtl_or(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(or);
      }
      else if(decinfo.isa.instr.funct3==7){
          rtl_and(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(and);
      }
      else{
        printf("%08x\n",cpu.pc);
        assert(0);
      }
  }
  else if(decinfo.opcode==32){
      if(decinfo.isa.instr.funct3==0){
          rtl_sub(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(sub);
      }
      else if(decinfo.isa.instr.funct3==5){
          t0 = id_src2->val & 0b11111;
          rtl_sar(&id_dest->val, &id_src->val, &t0);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(sra);
      }
      else{
        printf("%08x\n",cpu.pc);
        assert(0);
      }
  }
  else if(decinfo.opcode==1){
      if(decinfo.isa.instr.funct3==0){
          rtl_imul_lo(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(mul);
      }
      else if(decinfo.isa.instr.funct3==1){
          rtl_imul_hi(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(mulh);
      }
      else if(decinfo.isa.instr.funct3==4){
          rtl_idiv_q(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(div);
      }
      else if(decinfo.isa.instr.funct3==5){
          rtl_div_q(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(divu);
      }
      else if(decinfo.isa.instr.funct3==6){
          rtl_idiv_r(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(rem);
      }
      else if(decinfo.isa.instr.funct3==7){
          rtl_div_r(&id_dest->val, &id_src->val, &id_src2->val);
          rtl_sr(id_dest->reg, &id_dest->val, 4);

          print_asm_template2(remu);
      }
      else{
        printf("%08x %d\n",cpu.pc,decinfo.isa.instr.funct3);
        assert(0);
      }
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