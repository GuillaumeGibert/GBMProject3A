# GBMProject3A

Description :
-------------

This is a starting point if you wish to measure physiological data using Arduino and to process it using C++. 

Prerequisites:
--------------

You should install Qt (https://www.qt.io/) and Arduino (https://www.arduino.cc/en/Main/Software) for your platform.

Content :
---------
![Structure] (doc/images/GBMProject3A_structure.jpg?raw=true "Structure")

* A dummy ino file that sends through the serial port the analog input values read on the arduino
* A class called SerialPortManager based on QTSerialPort gets data from the serial port, segments it and emits the corresponding vector of floats with timestamp.
* A class called SineGenerator emits a series of sine signals with timestamp (to be used if you do not have access to an Arduino)
* A dummy class called SignalProcessing gets the vector of floats on its slot setInputData and filters it (IIR filter).
* A class called Buffering stores data from SerialPortManager or SineGenerator and creates buffer of data before sending it.
* A class called FFT computes the power and phase spectrum of a given buffer of data
* A display class called TemporalSignalDisplay gets the vector of floats on its slot setNewValues and display it.
* A display class called BufferedSignalDisplay gets (either temporal or frequency) buffer of data  and display it.

![Screenshot] (https://github.com/GuillaumeGibert/GBMProject3A/blob/develop/doc/images/GBMProject3A_screenshot.jpg?raw=true "Screenshot")

Installation :
-------------

* Either clone (git clone https://github.com/GuillaumeGibert/GBMProject3A.git using a git client) or download the project
* Upload the ino project to your Arduino
* Open the C++ project using the GBMProject3A.pro file
* Compile and Run it

The analog input values received by the SignalProcessing object are displayed on the screen together with its power spectrum and (low-pass) filtered ones.

Feel free to modify the code to fit your needs!

