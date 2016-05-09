#ifndef signalmover_h
#define signalmover_h

#include <arduino.h>
#include <Bounce2.h>
#include <servomover.h>


class SingleSignalMover
{
 public:
  SingleSignalMover(LinearServoMover *upper_arm,
                    int hp1_button_pin);
  void init();
  void perhaps_update();

 private:
  Bounce hp1_button;
  int hp1_button_pin;
  LinearServoMover *upper_arm;
};


class DualSignalMover
{
 public:
  DualSignalMover(LinearServoMover *upper_arm,
                  int hp1_button_pin,
                  LinearServoMover *lower_arm,
                  int hp2_button_pin);
  void init();
  void perhaps_update();

 private:
  Bounce hp1_button;
  Bounce hp2_button;
  int hp1_button_pin;
  int hp2_button_pin;
  LinearServoMover *upper_arm;
  LinearServoMover *lower_arm;
};


class SwitchMover
{
 public:
  SwitchMover(LinearServoMover *switch_servo,
              int button_pin,
              int relais_pin);
  void init();
  void perhaps_update();

 private:
  Bounce button;
  int button_pin;
  int relais_pin;
  LinearServoMover *switch_servo;
};

#endif
