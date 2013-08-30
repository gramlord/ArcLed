/*
  This is a simple led flasher. It uses the ArcSched library to either turn the
  led on, turn it off, flash it for a given length of time, or on and off in
  various combinations. See the comments below.
  
  Copyright 2013 Graeme Elsworthy, Arcsine Pty Ltd, graeme@arcsine.com.au
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
*/

#include <ArcLed.h>
#include <ArcSched.h>

ArcLed led;
ArcSched sched;

void setup() {
  sched.setup();  // set up the scheduler first
  led.setup(13, &sched);  // pin and scheduler
  
  // Uncomment whichever takes your fancy. All numbers in milli seconds.
  // led.on();
  // led.off();
  // led.flash(500);                      // one-off flash for this duration
  // led.flash(50, 1950);                 // on, off repeatedly
  // led.flash(50, 200, 50, 1700);        // on, off, on, off repeatedly
  led.flash(50, 200, 50, 200, 50, 1450);  // on, off, on, off, on, off repeatedly
}

void loop() {
  sched.loop();
}
