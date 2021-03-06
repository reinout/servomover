Servo/signal mover library
==========================

Arduino library to move servo's (slowly) with a linear movement. It wraps the
standard servo library.

Note: later on I might add other kinds of movement by adding more classes. And
I might switch my naming style. Currently it is python-inspired as I'm used to
it...


Servo wrapper
-------------

Usage::

  #include <Servo.h>
  #include <servomover.h>

  LinearServoMover upper_arm = LinearServoMover(11, 1300, 1750, 1200);

  void setup() {
    upper_arm.init();
    upper_arm.move_to_max();
   }

  void loop() {
    upper_arm.perhaps_update();
  }

You need to instantiate the ``LinearServoMover`` class with

- pin number

- min position (in ms)

- max position (in ms)

- duration (in ms)

Then, call ``.init()`` on it and make sure the loop hits ``.perhaps_update()``

Afterwards you can call ``.move_to_max()`` or ``.move_to_min()`` to begin a
movement to the min or max position.


Signal wrapper
--------------

Usage::

    #include <Servo.h>
    #include <servomover.h>
    #include <signalmover.h>
    #include <Bounce2.h>

    LinearServoMover upper_arm = LinearServoMover(11, 1301, 1750, 1200);
    LinearServoMover lower_arm = LinearServoMover(12, 1150, 1750, 1200);
    int HP1_BUTTON_PIN = 2;
    int HP2_BUTTON_PIN = 3;

    DualSignalMover signal = DualSignalMover(&upper_arm, HP1_BUTTON_PIN,
                                             &lower_arm, HP2_BUTTON_PIN);


    void setup() {
      signal.init();
    }


    void loop() {
      signal.perhaps_update();
    }

The example is for a ``DualSignalMover``, the same applies to ``SingleSignalMover``.

You need to set up a servo mover for one or two servos, first.

The signal mover is initialized with:

- A pointer at a servo mover.

- A pin number for a button.

(For a signal with two arms you need two of them, of course, like in the example).

The **button** is a pin that is kept high by default by initializing it as a
``INPUT_PULLUP``. Attach the pin to GND (and keep it there) and the signal
will move.

This way you only need one wire for a hp0/hp1 signal and two for a hp0/hp1/hp2
signal. The hp0 ("stop) state is the default when the signal is in rest. hp1
or hp2 are deliberately switched. Advantage of steering a signal with an
arduino!

**TODO**: perhaps I need to adjust the wording. "Button" might not be the best
name as it suggest a push button that sends a pulse.


Pulse mover
------------

Usage::

  #include <servomover.h>  /* Only for automatic library detection */
  #include <Servo.h>  /* Only for automatic library detection */
  #include <pulsemover.h>
  #include <Bounce2.h>

  int MAIN_BASE = 7;
  int MAIN_ACTUATED = 8;
  int HP1_BUTTON_PIN = 2;

  PulseMover upper_arm = PulseMover(MAIN_BASE, MAIN_ACTUATED);

  void setup() {
    hp1_button.attach(HP1_BUTTON_PIN, INPUT_PULLUP);
    hp1_button.interval(20);
    upper_arm.init();
   }

  void loop() {
    hp1_button.update();
    if (hp1_button.fell() ) {
      /* fell = pulled to ground, which means activated */
      upper_arm.move_to_actuated();
    }
    if (hp1_button.rose() ) {
      /* Back to default */
      upper_arm.move_to_base();
    }
    upper_arm.perhaps_update();
  }

You need to instantiate the ``PulseMover`` class with

- pin number for connection that, when made positive, swiches on a
  MOSFET/transistor that gives power to the magnet that pulls the arm to the
  base position.

- Similarly pin number for the actuated position.

Then, call ``.init()`` on it and make sure the loop hits ``.perhaps_update()``

Afterwards you can call ``.move_to_base()`` or ``.move_to_actuated()`` to move
to those positions.

Note: the pulse duration is currently hardcoded to 1 second.
