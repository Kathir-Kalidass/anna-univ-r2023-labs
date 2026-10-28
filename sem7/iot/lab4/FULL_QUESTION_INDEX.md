# Full 8051 practical question index

The original list contains many prompts that are the **same program with a different delay, text, peripheral module, or explanation request**. They are all accounted for below. A source filename means a runnable MCU-IDE/SDCC program; `edit:` means change the labelled constant/text in that runnable source; `note:` means it is a viva explanation, collected in the README and `30_stack_context_notes.md` rather than falsely presented as hardware code.

## GPIO (20)

1 blink `01_gpio_blink.c`; 2 500 ms `01_gpio_blink.c`; 3 timer blink `08_timer0_blink_polling.c`; 4 switch toggle `06_switch_toggle_debounce.c`; 5 alternate `02_gpio_alternate_leds.c`; 6 sequence `03_gpio_running_left.c`; 7 left `03_gpio_running_left.c`; 8 right: edit its shift direction; 9 Knight Rider `04_gpio_knight_rider.c`; 10 all toggle `31_gpio_all_leds_toggle.c`; 11 read switch `05_switch_mirror.c`; 12 press counter `07_switch_press_counter.c`; 13 long/short `33_long_short_press.c`; 14 debounce `06_switch_toggle_debounce.c`; 15 LED while pressed: edit `05_switch_mirror.c` to `P1=!P0`; 16 toggle press `06_switch_toggle_debounce.c`; 17 two switches: edit `05_switch_mirror.c`; 18 P1→P2: edit `18_gpio_mirror_port.c`; 19 mirror `05_switch_mirror.c`; 20 door lock `32_gpio_door_lock.c`.

## Timers and counters (30)

1/10/100 ms `lab4_common.h:timer0_ms`; 1 second `10_timer1_one_second.c`; Timer0 blink `08_timer0_blink_polling.c`; Timer1 blink `10_timer1_one_second.c`; overflow toggle `09_timer0_interrupt_blink.c`; LCD timer `37_lcd_stopwatch.c`; square waves `11_timer_square_wave.c`; interrupt timer `09_timer0_interrupt_blink.c`; stopwatch `37_lcd_stopwatch.c`; countdown `38_lcd_countdown.c`; traffic `25_traffic_signal_timer.c`; buzzer `35_timer_buzzer_each_second.c`; warning flash `34_timer_warning_flash.c`; relay `36_timer_relay_control.c`; sensor every 500 ms `50_timer_sensor_scheduler.c`; scheduler `50_timer_sensor_scheduler.c`; timer-vs-delay: note README. External-pulse count `12_counter_external_pulses.c`; visitor/product/wheel/push count `13_counter_visitor_int0.c`/`07_switch_press_counter.c`; RPM: `12_counter_external_pulses.c` plus fixed timing window; reset after 100: edit `13_counter_visitor_int0.c`; LCD count `20_lcd_counter.c`; timer/counter comparison: note README; fixed-pulse interrupt: edit `12_counter_external_pulses.c` and check `TL0`.

## UART (20)

Send char/string `14_uart_send_hello.c`; receive/echo `15_uart_receive_echo.c`; receive string `44_uart_receive_string.c`; periodic send `14_uart_send_hello.c`; switch status `43_uart_send_switch.c`; sensor data `45_uart_sensor_value.c`; LED command `16_uart_command_led.c`; GSM `46_uart_gsm_command.c`; GPS/ESP8266/HC-05: `47_uart_bluetooth_led.c` (same 9600 UART transport; module protocol differs); received LCD char `22_uart_to_lcd.c`; serial interrupt `17_uart_serial_interrupt.c`; transmit/receive functions `lab4_common.h`; baud/SBUF/SCON/TI/RI: README; serial terminal `15_uart_receive_echo.c`.

## LCD (20)

HELLO `18_lcd_hello.c`; name/roll/WELCOME: edit `18_lcd_hello.c` or `39_lcd_roll_number.c`; register/switch/counter/timer/UART character: `19_lcd_switch_status.c`,`20_lcd_counter.c`,`37_lcd_stopwatch.c`,`22_uart_to_lcd.c`; scroll left/right `21_lcd_scroll.c`,`42_lcd_scroll_right.c`; blink `40_lcd_blink_message.c`; clear after 5 seconds: edit `18_lcd_hello.c` with `delay_ms(5000);lcd_cmd(1)`; temperature/voltage: use `45_uart_sensor_value.c` input and LCD routines; visitor count `20_lcd_counter.c`; time `37_lcd_stopwatch.c`; menu `41_lcd_menu.c`; 4-bit mode and initialization theory: README (this pack uses the simpler 8-bit lab wiring).

## Interrupt, stack, context and mixed applications

Interrupt toggle/count/timer/serial/priority/emergency: `23_external_interrupt_toggle.c`,`49_interrupt_count.c`,`09_timer0_interrupt_blink.c`,`17_uart_serial_interrupt.c`,`48_interrupt_priority.c`,`24_emergency_stop.c`. ISR, vectors, RET/RETI, enable/disable, nesting, latency, polling: README. PUSH/POP, SP, nested calls, return address, LIFO: `27_stack_push_pop.c` and `30_stack_context_notes.md`. Two task, LED+UART/LCD/sensor/traffic/home/irrigation scheduling: `28_round_robin_tasks.c`,`29_timer_task_switch.c`,`26_timer_uart_lcd_gpio.c`,`25_traffic_signal_timer.c`,`50_timer_sensor_scheduler.c`; context/register/separate-stack questions: `30_stack_context_notes.md`. Mixed questions map to `26_timer_uart_lcd_gpio.c`, `22_uart_to_lcd.c`, `20_lcd_counter.c`, `24_emergency_stop.c`, `47_uart_bluetooth_led.c`.

## “What if?” viva bank

TI/RI not cleared, missing timer load/TRx, EA=0, RET vs RETI, stack overflow/shared stack, bad baud, skipped LCD initialization, uncleared TF0, crystal selection, hardware timer vs delay, interrupt UART vs polling: see the **High-value viva reminders** in `README.md` and the stack note. These have no honest standalone hardware “output”; they are explained as cause/effect answers there.
