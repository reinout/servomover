#include <arduino.h>
#include <Servo.h>
#include "servomover.h"

int PERIOD = 20;  // Fixed, a servo can be steered every 20ms.


LinearServoMover::LinearServoMover(int pin,
                                   int min_position,
                                   int max_position,
                                   int duration){
  LinearServoMover::pin = pin;
  LinearServoMover::min_position = min_position;
  LinearServoMover::max_position = max_position;
  LinearServoMover::duration = duration;

  current_position = min_position;
  next_update = millis();
  to_min = true;
  done = true;
}

void LinearServoMover::init(){
  movement_per_period = (max_position - min_position) * PERIOD / duration;
  servo.attach(pin);
  servo.writeMicroseconds(current_position);
  next_update = millis() + PERIOD;
}

void LinearServoMover::move_servo(){
  if (current_position <= min_position) {
    current_position = min_position;
    done = true;
  }
  if (current_position >= max_position) {
    current_position = max_position;
    done = true;
  }
  servo.writeMicroseconds(current_position);
  if (done) {
    servo.detach();
  }
}

void LinearServoMover::move_to_min(){
  to_min = true;
  done = false;
  servo.attach(pin);
}

void LinearServoMover::move_to_max(){
  to_min = false;
  done = false;
  servo.attach(pin);
}

void LinearServoMover::perhaps_update(){
  if (!done && next_update < millis()) {
    next_update = millis() + PERIOD;
    if (to_min) {
      current_position -= movement_per_period;
    }
    else {
      current_position += movement_per_period;
    }
    move_servo();
  }
}
