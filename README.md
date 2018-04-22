BamocarControlBoard
===================

This repositroy contains configuration and program for STM32303RE board, 
used as a control and communication platform with Unitek's Bamocar Servo Amplifier.

Following architecture has been applied:
----------------------------------------

* board communicates with Bamocar via CAN bus
* board communicates with computer via UART
* tests are applied using Python and [pyserial](https://pythonhosted.org/pyserial/) module

This repository is effect of activity in [AGH Racing Team](http://www.racing.agh.edu.pl/)
