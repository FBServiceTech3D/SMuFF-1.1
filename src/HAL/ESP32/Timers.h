#pragma once

struct ESP32_timer_t {
  hw_timer_t* timer;
  portMUX_TYPE mux;
  void (*ISRptr) (void);
  void (*serviceFunPtr)(void);
  };

void IRAM_ATTR ISR1();
void IRAM_ATTR ISR2();
void IRAM_ATTR ISR3();
void IRAM_ATTR ISR4();
