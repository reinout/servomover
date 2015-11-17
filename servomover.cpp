#include <arduino.h>
#include "servomover.h"

unsigned long PERIOD = 20;  // Fixed, a servo can be steered every 20ms.


LinearServoMover::LinearServoMover(int pin,
                                   int min_position,
                                   int max_position,
                                   int duration){
  pin = pin;
  min_position = min_position;
  max_position = max_position;
  duration = duration;

  current_position = min_position;
  next_update = 0;
  to_min = true;
  done = true;

  servo.attach(pin);
  move_servo();
  movement_per_period = (max_position - min_position) / duration * PERIOD;
}

void LinearServoMover::move_servo(){
  if (current_position < min_position) {
    current_position = min_position;
    done = true;
  }
  if (current_position > max_position) {
    current_position = max_position;
    done = true;
  }
  servo.writeMicroseconds(current_position);
}

void LinearServoMover::move_to_min(){
  to_min = true;
  done = false;
  return;
}

void LinearServoMover::move_to_max(){
  to_min = false;
  done = false;
  return;
}

void LinearServoMover::perhaps_update(){
  unsigned long now = millis();
  if (!done && next_update < now) {
    next_update = now + PERIOD;
    if (to_min) {
      current_position -= movement_per_period;
    }
    else {
      current_position += movement_per_period;
    }
    move_servo();
  }
}
