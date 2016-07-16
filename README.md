# CoreNG

Hardware abstraction layer for RepRapFirmware based on Atmel ASF 3.31

> This repository is a fork of [dc42's CoreNG](https://github.com/dc42/CoreNG)
> but with additions to build using the scons command line tool rather than
> the Eclipse IDE.  See the file `INSTALL.md` for instructions on
> how to build this fork for RADDS v1.5 electronics.

This is a new hardware abstraction layer for RepRapFirmware based on
the Atmel Software Framework (ASF) 3.31 with some additional modules
from the Arduino Due core.  CoreNG replaces the [CoreDuet
project](https://github.com/dcnewman/CoreDuet) in releases 1.11 and later
of the [dc42 fork of the
RepRapFirmware](https://github.com/dc42/RepRapFirmware).

The main advantages over the previous CoreDuet project are support for more
recent Atmel SAM processors (including the one used in the next-generation
Duet), support for PWM outputs via timer/counter channels, and the use of
the on-chip hardware ADC scheduler.  Also the USB interface is interrupt
and DMA driven instead of polled.

To build it, import the project into [Eclipse](https://eclipse.org/)
Mars.2, select the desired configuration (SAM3X8E or SAM4E8E), and
press Build.  Or, if you dislike IDEs, then use the
[scons](http://scons.org/) command line tool as per the directions
found in the `INSTALL.md` file.

License: GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html.
