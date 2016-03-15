#ifndef pulsemover_h
#define pulsemover_h

#include <arduino.h>


class PulseMover
{
 public:
  PulseMover(int pin_base,
             int pin_actuated);
  void init();
  void move_to_base();
  void move_to_actuated();
  void perhaps_update();

 private:
  int pin_base;
  int pin_actuated;
  unsigned long stop_pulse_again;
  bool done;
};

#endif
