Normally, the CoreNG repo is built using the Eclipse IDE.  This
fork of the CoreNG sources may also be built using the
[scons](http://scons.org/) command line tool.  Moreover, the scons
build supports RADDS electronics as well as Duet and DuetNG.  If
you wish to use Eclipse and build for RADDS, then you will need to
modify the Eclipse Project files to do so.

To build follow the steps listed below.

1. Should your system lack Python 2.x, download and install it.

2. Download and install [scons](http://scons.org/).  Version 2.3.5 or
   later is required.

3. Install the [Arduino](https://www.arduino.cc/) application.
   Version 1.5.8beta is known to work.  You will merely be using the
   gcc-arm toolchain installed with/by the Arduino application.
   
4. Run the Arduino application and install the ARM programming tools.
   Look under "Tools > Board > Boards Manager...".  Select the "Arduino
   SAM Boards (32-bits ARM Cortex-M3) by Arduino" and install it.

5. From this github repository, edit the file

       sample_rrf_arduino_paths.py

   as appropriate to indicate the location of your installed Arduino
   application and gcc tools.  Then save this file to your home directory
   as the file

       ~/.rrf_arduino_paths.py

6. From the top-level CoreNG repository directory, build the
   library for RADDS with the command

       scons platform=radds

   For Duet, instead use either command

       scons
       
   or
   
       scons platform=duet

   And for DuetNG,

       scons platform=ng

   Once scons finishes a build, the resulting library will be one of

       RADDS:  RADDS/libCoreNG.a
       Duet:   SAM3X8E/libCoreNG.a
       DuetNG: SAM4E8E/libCoreNG.a
