# Stack and context-switching viva answers

- **PUSH** stores a byte at `SP+1`; **POP** restores the byte at `SP` then decrements SP. The stack is LIFO.
- `CALL` pushes the return address; `RET` pops it. An ISR must finish with `RETI`, which also informs the interrupt controller that service is complete.
- Before changing tasks, save ACC, B, PSW, R0–R7, DPTR and the task's SP. Restore the selected task's SP and registers before continuing it.
- Each task needs a separate stack. Sharing one corrupts return addresses/register values when tasks nest calls or are interrupted.
- `27_stack_push_pop.c` is a real PUSH/POP demonstration. `28_round_robin_tasks.c` and `29_timer_task_switch.c` are safe MCU-IDE scheduler simulations; they do not claim to be a production pre-emptive RTOS.
