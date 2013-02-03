#include <cpu-state.h>


struct cpu_state *i386_common_isr(struct cpu_state *state)
{
    return state;
}


void i386_syscall(struct cpu_state *state)
{
    (void)state;
}
