#ifndef servomover_h
#define servomover_h

#include <arduino.h>
#include <Servo.h>


class LinearServoMover
{
 public:
  LinearServoMover(int pin,
                   int min_position,
                   int max_position,
                   int duration);
  void init();
  void perhaps_update();
  void move_to_min();
  void move_to_max();

 private:
  int pin;
  int min_position;
  int max_position;
  int duration;

  int movement_per_period;
  int current_position;
  unsigned long next_update;
  bool to_min;
  bool done;

  Servo servo;
  void move_servo();
};

#endif
