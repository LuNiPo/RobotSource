# RobotSource
Files and informations correlating to my bachelors thesis.
for more Informations see my thingiverse page : [link ](https://www.thingiverse.com/thing:5073264/)

The included programs are used to control the holonomic robot. driver.py is executed on the RaspberryPi. the other scripts on the Arduino MEGA with RAMPS. Raspberrypi and Mega must be connected serially. In the code of the driver.py the device name must be adapted. 

## List of Programs:

* driver.py: Used on RaspberryPi for sending ROS Cmd_vel Messages via serial (115200Bd) to RAMPS Stack sends messages in format <x,y,w> via serial
* src/cupdate: Libary to generate wheel frequencies for the StepperMotor Drivers.

   Generate Update object with ```Cupdate updater( sP1, sP2, sP3, sP4, dP1, dP2, dP3, dP4, wheelDia ; StepsRev ; xWheelDistance, yWheelDistance);```
   
   Calculate Wheel velocitys using ```updater.calcVelocity(x_vel, y_vel, omega);```
   
   Generate step signals using ```updater.run();``` (note: this function must be called cyclically, therfore delay() may not be used).

* mega.ino: Progamm which is run on the Arduino mega.

**Note: Im not an expert programmer therefore parts of the programms may are botched together badly. Feel free to improve**
