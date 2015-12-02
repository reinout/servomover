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


DualSignalMover::DualSignalMover(LinearServoMover *upper_arm,
                                 int hp1_button_pin,
                                 LinearServoMover *lower_arm,
                                 int hp2_button_pin) {
  DualSignalMover::hp1_button = Bounce();
  DualSignalMover::hp1_button_pin = hp1_button_pin;
  DualSignalMover::upper_arm = upper_arm;
  DualSignalMover::hp2_button = Bounce();
  DualSignalMover::hp2_button_pin = hp2_button_pin;
  DualSignalMover::lower_arm = lower_arm;
}

void DualSignalMover::init() {
  hp1_button.attach(hp1_button_pin, INPUT_PULLUP);
  hp1_button.interval(20);
  upper_arm->init();
  hp2_button.attach(hp2_button_pin, INPUT_PULLUP);
  hp2_button.interval(20);
  lower_arm->init();
}

void DualSignalMover::perhaps_update() {
  hp1_button.update();
  hp2_button.update();

  if (hp1_button.rose() ) {
    upper_arm->move_to_min();
    lower_arm->move_to_min();
  }
  if (hp1_button.fell() ) {
    upper_arm->move_to_max();
    lower_arm->move_to_min();
  }
  if (hp2_button.rose() ) {
    upper_arm->move_to_min();
    lower_arm->move_to_min();
  }
  if (hp2_button.fell() ) {
    upper_arm->move_to_max();
    lower_arm->move_to_max();
  }

  upper_arm->perhaps_update();
  lower_arm->perhaps_update();
}
