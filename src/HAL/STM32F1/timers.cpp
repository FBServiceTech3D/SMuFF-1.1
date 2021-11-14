/**
 * SMuFF Firmware
 * Copyright (C) 2019-2021 Technik Gegg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#if defined(__STM32F1__)

/*
 * STM32F1 HAL timers handling
 */
#include <Arduino.h>
#include "timers.h"

#if defined(__LIBMAPLE__)
static struct {
  HardwareTimer timer;
  void (* serviceFunPtr)(void);
  } timers[] = {
    { .timer = HardwareTimer(1),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(2),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(3),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(4),
      .serviceFunPtr = nullptr },
  #ifdef STM32_HIGH_DENSITY
    { .timer = HardwareTimer(5),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(6),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(7),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(8),
      .serviceFunPtr = nullptr }
  #endif
};
#else
static struct {
  HardwareTimer timer;
  void (* serviceFunPtr)(void);
  } timers[] = {
    { .timer = HardwareTimer(TIM1),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(TIM2),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(TIM3),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(TIM4),
      .serviceFunPtr = nullptr },
  #ifdef STM32_HIGH_DENSITY
    { .timer = HardwareTimer(TIM5),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(TIM6),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(TIM7),
      .serviceFunPtr = nullptr },
    { .timer = HardwareTimer(TIM8),
      .serviceFunPtr = nullptr }
  #endif
};
#endif

void timerISRService(ZTimer::timerNum_t t) {
  if (timers[t].serviceFunPtr != nullptr)
    timers[t].serviceFunPtr();
}

void ISR1() {
  timerISRService(ZTimer::_TIMER1);
}

void ISR2() {
  timerISRService(ZTimer::_TIMER2);
}

void ISR3() {
  timerISRService(ZTimer::_TIMER3);
}

void ISR4() {
  timerISRService(ZTimer::_TIMER4);
}

#ifdef STM32_HIGH_DENSITY
void ISR5() {
  timerISRService(ZTimer::_TIMER5);
}

void ISR6() {
  timerISRService(ZTimer::_TIMER6);
}

void ISR7() {
  timerISRService(ZTimer::_TIMER7);
}

void ISR8() {
  timerISRService(ZTimer::_TIMER8);
}
#endif

void ZTimer::setupTimer(timerNum_t timer, timerChannel_t channel, uint32_t prescaler, timerVal_t compare) {
  if (timer < _TIMER1 || timer >= MAX_TIMERS)
    return;

  _timer = timer;
  _channel = channel;

  HardwareTimer * hwTimer = &timers[_timer].timer;
  hwTimer->pause();
  noInterrupts();
  if (_timer == _TIMER6 || _timer == _TIMER7) {
    // since these timers don't have a compare mode, we're using
    // the compare value as a period (in uS)
    hwTimer->setPrescaleFactor(prescaler);
    #if defined(__LIBMAPLE__)
    hwTimer->setPeriod(compare);
    #else
    //hwTimer->setPWM(channel, _pin, _frequency, _dutyCycle);
    #endif
  }
  else {
    hwTimer->setMode(channel, TIMER_OUTPUT_COMPARE);
    hwTimer->setPrescaleFactor(prescaler);
    #if defined(__LIBMAPLE__)
    hwTimer->setCompare(channel, compare);
    #else
    hwTimer->setCaptureCompare(channel, compare);
    #endif
  }
  hwTimer->attachInterrupt(channel, ((void (*[])(void)) { &ISR1, &ISR2, &ISR3, &ISR4,
#ifdef STM32_HIGH_DENSITY
    &ISR5, &ISR6, &ISR7, &ISR8,
#endif
    })[_timer]);
  interrupts();
}

void ZTimer::setupHook(void (*function)(void)) {
  if (_timer != UNDEFINED)
    timers[_timer].serviceFunPtr = function;
}

void ZTimer::setNextInterruptInterval(timerVal_t interval) {
  if (_timer == UNDEFINED)
    return;

  stop();
  setOverflow(interval);
  timers[_timer].timer.setCount(0);
  start();
}

timerVal_t ZTimer::getOverflow() {
  return (_timer != UNDEFINED) ? timers[_timer].timer.getOverflow() : 0;
}

void ZTimer::setOverflow(timerVal_t value) {
  if (_timer != UNDEFINED)
    timers[_timer].timer.setOverflow(value);
}

void ZTimer::start() {
  if (_timer != UNDEFINED) {
    HardwareTimer * hwTimer = &timers[_timer].timer;
    hwTimer->refresh();
    hwTimer->resume();
  }
}

void ZTimer::stop() {
  if (_timer != UNDEFINED)
    timers[_timer].timer.pause();
}

#endif // __STM32F1__
