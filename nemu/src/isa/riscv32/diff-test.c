#include "nemu.h"
#include "monitor/diff-test.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool flag=true;
  for(int i = 0; i < 32; i++){
      if(reg_l(i) != ref_r->gpr[i]._32){
          printf("%08x\n",pc);
          printf("Error in %s, qemu:0x%08x, nemu:0x%08x\n", reg_name(i, 32), ref_r->gpr[i]._32, reg_l(i));
          flag=false;
      }
  }
  return flag;
}

void isa_difftest_attach(void) {
}
