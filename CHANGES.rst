Changelog for servomover
========================

0.5 (unreleased)
----------------

- Nothing changed yet.


0.4 (2016-03-16)
----------------

- Added 'pulsemover' for steering with pulses, for instance for viessmann
  slow-moving magnet-based signals. Also useful for cheap conrad switch motors
  later on.
  [reinout]


0.3 (2015-12-02)
----------------

- Added signal wrapping class for signals with one arm and also one for two
  arms.
  [reinout]

- The servo is reliably detached also in the initial state. Previously, the
  servo would stay attached until after the first movement.
  [reinout]


0.2 (2015-11-17)
----------------

- Servo now gets 20 milliseconds to reach the initial position before the
  servo is detached. This way I get the fixed initial position *without* any
  dithering.
  [reinout]

- Note: this is a fully working version. I can steer a german hp0/hp1/hp2
  signals with two servos with this library!
  [reinout]


0.1 (2015-11-17)
----------------

- Started the library. Quite some inspiration was taken from
  https://github.com/aukehuizinga/arduinoServoWrapper.
  [reinout]

- Got the first version working. Had to learn c++ in the process.
  [reinout]

- Added usage documentation in the README.
  [reinout]
