# GBMProject3A

Description :
-------------

This is a starting point if you wish to measure physiological data using Arduino and to process it using C++. 

Prerequisites:
--------------

You should install Qt (https://www.qt.io/) and Arduino (https://www.arduino.cc/en/Main/Software) for your platform.

Content :
---------
* A class called SerialPortManager based on QTSerialPort gets data from the serial port, segments it and emits the corresponding vector of floats.
* A dummy class called SignalProcessing gets the vector of floats on its slot setInputData.
* A display class called TemporalSignalDisplay gets the vector of floats on its slot setNewValues and display it.
* A dummy ino file that sends through the serial port the analog input values read on the arduino

Installation :
-------------

* Either clone (git clone https://github.com/GuillaumeGibert/GBMProject3A.git using a git client) or download the project
* Upload the ino project to your Arduino
* Open the C++ project using the GBMProject3A.pro file
* Compile and Run it

The analog input values received by the SignalProcessing object are displayed on the screen.

Feel free to modify the code to fit your needs!

