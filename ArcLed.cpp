/*
  ArcLed is a simple led blinker and flasher.

  Copyright 2013 Graeme Elsworthy, Arcsine Pty Ltd, graeme@arcsine.com.au
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

#include <ArcLed.h>
#include <ArcSched.h>

void ArcLed::setup(uint8_t p, ArcSched *s) {
  pin = p;
  sched = s;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void ArcLed::on() {
  char name[16];

  digitalWrite(pin, HIGH);
  sprintf(name, "AL%02d", pin);
  sched->deregisterFunction(name);
}

void ArcLed::off() {
  char name[16];

  digitalWrite(pin, LOW);
  sprintf(name, "AL%02d", pin);
  sched->deregisterFunction(name);
}

void ArcLed::toggle() {
  digitalWrite(pin, ! digitalRead(pin));
}

void _ledFlashOnce(SchedFunctionDetail *fd, void *arg) {
  ArcLed *led = (ArcLed *) arg;

  led->off();
}

void _ledFlash(SchedFunctionDetail *fd, void *arg) {
  ArcLed *led = (ArcLed *) arg;
  uint8_t ledValue;

  led->toggle();
  ledValue = digitalRead(led->pin);
  led->sched->setInterval(fd, ledValue == LOW ? led->ledOffDuration[led->flashIndex++] : led->ledOnDuration[led->flashIndex]);
  if(led->flashIndex >= led->flashIndexMax)
    led->flashIndex = 0;
}

void ArcLed::flash(uint32_t onDuration) {
  char name[16];

  sprintf(name, "AL%02d", pin);
  on();
  (void) sched->registerFunction(_ledFlashOnce, this, name, SchedPriorityLow, onDuration);
}

void ArcLed::flash(uint32_t on0, uint32_t off0) {
  char name[16];

  sprintf(name, "AL%02d", pin);
  on();
  ledOnDuration[0] = on0;
  ledOffDuration[0] = off0;
  flashIndex = 0;
  flashIndexMax = 1;
  (void) sched->registerFunction(_ledFlash, this, name, SchedPriorityLow, on0);
}

void ArcLed::flash(uint32_t on0, uint32_t off0, uint32_t on1, uint32_t off1) {
  char name[16];

  sprintf(name, "AL%02d", pin);
  on();
  ledOnDuration[0] = on0;
  ledOffDuration[0] = off0;
  ledOnDuration[1] = on1;
  ledOffDuration[1] = off1;
  flashIndex = 0;
  flashIndexMax = 2;
  (void) sched->registerFunction(_ledFlash, this, name, SchedPriorityLow, on0);
}

void ArcLed::flash(uint32_t on0, uint32_t off0, uint32_t on1, uint32_t off1, uint32_t on2, uint32_t off2) {
  char name[16];

  sprintf(name, "AL%02d", pin);
  on();
  ledOnDuration[0] = on0;
  ledOffDuration[0] = off0;
  ledOnDuration[1] = on1;
  ledOffDuration[1] = off1;
  ledOnDuration[2] = on2;
  ledOffDuration[2] = off2;
  flashIndex = 0;
  flashIndexMax = 3;
  (void) sched->registerFunction(_ledFlash, this, name, SchedPriorityLow, on0);
}
