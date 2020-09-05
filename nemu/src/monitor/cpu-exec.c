#include "nemu.h"
#include "monitor/monitor.h"
#include "monitor/watchpoint.h"
#include "monitor/expr.h"

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 10

/* restrict the size of log file */
#define LOG_MAX (1024 * 1024)

NEMUState nemu_state = {.state = NEMU_STOP};

void interpret_rtl_exit(int state, vaddr_t halt_pc, uint32_t halt_ret) {
  nemu_state = (NEMUState) { .state = state, .halt_pc = halt_pc, .halt_ret = halt_ret };
}

vaddr_t exec_once(void);
void difftest_step(vaddr_t ori_pc, vaddr_t next_pc);
void asm_print(vaddr_t ori_pc, int instr_len, bool print_flag);
void log_clearbuf(void);

static uint64_t g_nr_guest_instr = 0;

void monitor_statistic(void) {
  Log("total guest instructions = %ld", g_nr_guest_instr);
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  for (; n > 0; n --) {
    __attribute__((unused)) vaddr_t ori_pc = cpu.pc;

    /* Execute one instruction, including instruction fetch,
     * instruction decode, and the actual execution. */
    __attribute__((unused)) vaddr_t seq_pc = exec_once();

#if defined(DIFF_TEST)
  difftest_step(ori_pc, cpu.pc);
#endif

#ifdef DEBUG
  if (g_nr_guest_instr < LOG_MAX) {
    asm_print(ori_pc, seq_pc - ori_pc, n < MAX_INSTR_TO_PRINT);
  }
  else if (g_nr_guest_instr == LOG_MAX) {
    log_write("\n[Warning] To restrict the size of log file, "
              "we do not record more instruction trace beyond this point.\n"
              "To capture more trace, you can modify the LOG_MAX macro in %s\n\n", __FILE__);
  }
  log_clearbuf();

    /* TODO: check watchpoints here. */
    WP *head = gethead();
	  if (head) {
		    WP *p = head;
		    bool have_stop = false;
		while(p) {
			  bool flag = true;
			  uint32_t new_result = expr(p->expr,&flag);
			  if(!flag)
				    assert(0);
			  else {
				    if(p->result != new_result && !p->flag) {
					      printf("Watchpoint %d expr: %s\n%s(old value): %d\n%s(new value): %d\n", p->NO, p->expr,p->expr,p->result,p->expr,new_result);
					      p->result = new_result;
					      have_stop = true;
				    }
				    else if(p->result != new_result && p->flag) {
					      printf("Stop at breakpoint\n");
					      have_stop = true;
				    }
			  }
			  p = p->next;
		}
		if (have_stop) {
			//nemu_state = NEMU_STOP;
			//return;
			break;
		}
	}

#endif

  g_nr_guest_instr ++;

#ifdef HAS_IOE
    extern void device_update();
    device_update();
#endif

    if (nemu_state.state != NEMU_RUNNING) break;
  }

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_END: case NEMU_ABORT:
      _Log("nemu: %s\33[0m at pc = 0x%08x\n\n",
          (nemu_state.state == NEMU_ABORT ? "\33[1;31mABORT" :
           (nemu_state.halt_ret == 0 ? "\33[1;32mHIT GOOD TRAP" : "\33[1;31mHIT BAD TRAP")),
          nemu_state.halt_pc);
      monitor_statistic();
  }
}
