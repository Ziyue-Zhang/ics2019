#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(add) {

  rtl_add(&id_src->val, &id_src->val, &id_src2->val);
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(add);
}