#include <arduino.h>
#include "pulsemover.h"

int DURATION = 1000;  // Pulse should be given for one second.
/* int BASE = 1; */
/* int ACTUATED = 2; */

PulseMover::PulseMover(int pin_base,
                       int pin_actuated){
  PulseMover::pin_base = pin_base;
  PulseMover::pin_actuated = pin_actuated;

  stop_pulse_again = millis();
  done = true;
}

void PulseMover::init(){
  pinMode(pin_base, OUTPUT);
  digitalWrite(pin_base, LOW);
  pinMode(pin_actuated, OUTPUT);
  digitalWrite(pin_actuated, LOW);
  move_to_base();
  /* digitalWrite(pin_base, HIGH); */
  /* stop_pulse_again = millis() + PERIOD; */
}

void PulseMover::move_to_base(){
  done = false;
  digitalWrite(pin_actuated, LOW);
  digitalWrite(pin_base, HIGH);
  stop_pulse_again = millis() + DURATION;
}

void PulseMover::move_to_actuated(){
  done = false;
  digitalWrite(pin_base, LOW);
  digitalWrite(pin_actuated, HIGH);
  stop_pulse_again = millis() + DURATION;
}

void PulseMover::perhaps_update(){
  if (!done && stop_pulse_again < millis()) {
    digitalWrite(pin_base, LOW);
    digitalWrite(pin_actuated, LOW);
    done = true;
  }
}
