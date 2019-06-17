# GBMProject3A

Description :
-------------

This is a starting point if you wish to measure physiological data using Arduino and to process it using C++. 

Prerequisites:
--------------

You should install Qt (https://www.qt.io/) and Arduino (https://www.arduino.cc/en/Main/Software) for your platform.

Content :
---------

* A dummy ino file that sends through the serial port the analog input values read on the arduino
* A class called SerialPortManager based on QTSerialPort gets data from the serial port, segments it and emits the corresponding vector of floats with timestamp.
* A class called SineGenerator emits a series of sine signals with timestamp (to be used if you do not have access to an Arduino)
* A dummy class called SignalProcessing gets the vector of floats on its slot setInputData and filters it (IIR filter).
* A class called Buffering stores data from SerialPortManager or SineGenerator and creates buffer of data before sending it.
* A class called FFT computes the power and phase spectrum of a given buffer of data
* A display class called TemporalSignalDisplay gets the vector of floats on its slot setNewValues and display it.
* A display class called BufferedSignalDisplay gets (either temporal or frequency) buffer of data  and display it.

The current version of the software is structured as shown below. 

Signals are retrieved from either the SerialPortManager or the SineGenerator objects. The raw signals are sent to the MainWindow for display.

The raw signals are sent to the SignalProcessing object for filtering (IIR). The filtered signals are sent to the MainWindow for display.

The raw signals are also sent to the Buffering object that creates a buffer and sent it to the FFT object that computes the Power Spectrum.

The buffered signals as well as the Power spectrum are sent to the MainWindow for display.

![Structure](doc/images/GBMProject3A_structure.jpg?raw=true "Structure")

Screenshot :
-------------
At the top left corner, 2s window of raw signals updated at each time step (100 Hz in the example). 

At the top right corner, 2s window of filtered signals updated at each time step (same frequency as above).

At the bottom left corner, 2s window of raw buffered signals updated every 1s.

At the bottom right corner, Power spectrum updated for every new buffer (i.e. every 1s).

![Screenshot](doc/images/GBMProject3A_screenshot.jpg?raw=true "Screenshot")

Installation :
-------------

* Either clone (git clone https://github.com/GuillaumeGibert/GBMProject3A.git using a git client) or download the project
* Upload the ino project to your Arduino
* Open the C++ project using the GBMProject3A.pro file
* Compile and Run it

The analog input values received by the SignalProcessing object are displayed on the screen together with its power spectrum and (low-pass) filtered ones.

Feel free to modify the code to fit your needs!

