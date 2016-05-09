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


SwitchMover::SwitchMover(LinearServoMover *switch_servo,
                         int button_pin,
                         int relais_pin) {
  SwitchMover::button = Bounce();
  SwitchMover::button_pin = button_pin;
  SwitchMover::relais_pin = relais_pin;
  SwitchMover::switch_servo = switch_servo;
}

void SwitchMover::init() {
  button.attach(button_pin, INPUT_PULLUP);
  pinMode(relais_pin, OUTPUT);
  button.interval(20);
  switch_servo->init();
  button.update();
  // TODO: add this update/read to the signals, too
  if (button.read() == HIGH) {
    digitalWrite(relais_pin, HIGH);
  }
  else {
    digitalWrite(relais_pin, LOW);
  }
}

void SwitchMover::perhaps_update() {
  button.update();
  if (button.rose() ) {
    switch_servo->move_to_min();
    digitalWrite(relais_pin, HIGH);
  }
  if (button.fell() ) {
    switch_servo->move_to_max();
    digitalWrite(relais_pin, LOW);
  }
  switch_servo->perhaps_update();
}
