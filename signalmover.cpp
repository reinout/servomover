#include <arduino.h>
#include <Bounce2.h>
#include <servomover.h>
#include <signalmover.h>

int INITIAL_DELAY_MS = 2000;


SingleSignalMover::SingleSignalMover(LinearServoMover *upper_arm,
                                     int hp1_button_pin) {
  SingleSignalMover::hp1_button = Bounce();
  SingleSignalMover::hp1_button_pin = hp1_button_pin;
  SingleSignalMover::upper_arm = upper_arm;
}

void SingleSignalMover::init() {
  hp1_button.attach(hp1_button_pin, INPUT_PULLUP);
  hp1_button.interval(20);
  upper_arm->init();
}

void SingleSignalMover::perhaps_update() {
  hp1_button.update();
  if (hp1_button.rose() ) {
    upper_arm->move_to_min();
  }
  if (hp1_button.fell() ) {
    upper_arm->move_to_max();
  }
  upper_arm->perhaps_update();
}
