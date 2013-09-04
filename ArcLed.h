/*
  ArcLed is a simple led blinker and flasher.

  Copyright 2013 Graeme Elsworthy, Arcsine Pty Ltd, graeme@arcsine.com.au
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

#include <Arduino.h>
#include <ArcSched.h>

#ifndef _ArcLed_h
#define _ArcLed_h

class ArcLed {
  public:
    void setup(uint8_t, ArcSched *);

    // These functions define the API.
    void on();
    void off();
    void toggle();
    void flash(uint32_t);
    void flash(uint32_t, uint32_t);
    void flash(uint32_t, uint32_t, uint32_t, uint32_t);
    void flash(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

    // These are really private but need to be public because this is used through the scheduler.
    uint8_t pin;
    ArcSched *sched;
    uint32_t ledOnDuration[3];
    uint32_t ledOffDuration[3];
    uint8_t flashIndex;
    uint8_t flashIndexMax;
};

#endif
