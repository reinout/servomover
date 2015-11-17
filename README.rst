Servo mover library
===================

Arduino library to move servo's (slowly). It wraps the standard servo library


Usage::

  #include <Servo.h>
  #include <servomover.h>

  LinearServoMover upper_arm = LinearServoMover(11, 1300, 1750, 1200);
  LinearServoMover lower_arm = LinearServoMover(12, 1150, 1750, 1200);

  void setup() {
    upper_arm.init();
    upper_arm.move_to_max();
    lower_arm.move_to_max();
  }

  void loop() {
    upper_arm.perhaps_update();
    lower_arm.perhaps_update();
  }

You need to instantiate the ``LinearServoMover`` class with

- pin number

- min position (in ms)

- max position (in ms)

- duration (in ms)

Then, call ``.init()`` on it and make sure the loop hits ``.perhaps_update()``

Afterwards you can call ``.move_to_max()`` or ``.move_to_min()`` to begin a
movement to the min or max position.
