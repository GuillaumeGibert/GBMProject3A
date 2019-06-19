# GBMProject3A

Description :
-------------

This is a starting point if you wish to measure physiological data using Arduino and to process it using C++. 

Prerequisites:
--------------

You should install Qt (https://www.qt.io/) and Arduino (https://www.arduino.cc/en/Main/Software) for your platform.

Content :
---------
On the Arduino side:
* A dummy ino file that sends through the serial port the analog input values read on the arduino and listens to data coming from the PC connected using either USB or Bluetooth

On the PC side:
* A class called SerialPortManager based on QTSerialPort gets data from the serial port, segments it and emits the corresponding vector of floats with timestamp.
* A class called SineGenerator emits a series of sine signals with timestamp (to be used if you do not have access to an Arduino)
* A class called Spy that displays data emitted by either the SerialPortManager or the SineGenerator objects
* A dummy class called SignalProcessing gets the vector of floats on its slot setInputData and filters it (IIR filter).
* A class called Buffering stores data from SerialPortManager or SineGenerator and creates buffer of data before sending it.
* A class called FFT computes the power and phase spectrum of a given buffer of data
* A display class called TemporalSignalDisplay gets the vector of floats on its slot setNewValues and display it.
* A display class called BufferedSignalDisplay gets (either temporal or frequency) buffer of data  and display it.

Examples :
-------------
* ex1.cpp (GETTING DATA FROM ARDUINO USB) : a SerialPortManager object is created and then it listens to data emitted on the serial port by the Arduino. It is connected to a Spy object that display the retrieved data.
* ex2.cpp (GETTING DATA FROM ARDUINO BLUETOOTH) : a SerialPortManager object is created and then it listens to data emitted using Bluetooth (HC05 module for instance) by the Arduino. It is connected to a Spy object that display the retrieved data.
* ex3.cpp (GETTING DATA FROM SINE GENERATOR) : a SineGenerator object is created and then it generates sine signals. It is connected to a Spy object that display the generated signal values.
* ex4.cpp (DISPLAYING SIGNAL) : a SineGenerator object is created and then it generates sine signals. It is connected to a MainWindow object that diplays the signals.
* ex5.cpp (FILTERING SIGNALS) : a SineGenerator object is created and then it generates sine signals. It is connected to a SignalProcessing object that filters the signals. The raw and filtered signals are displayed by a MainWindow object.
* ex6.cpp (COMPUTING POWER SPECTRUM): a SineGenerator object is created and then it generates sine signals. It is connected to a Buffer object that creates buffer of signals and sends it to a FFT object. This object computes the Power Spectrum from this buffer. The raw signals and the Power Spectrum are displayed by a MainWindow object. 
* ex7.cpp (WRITING DATA TO ARDUINO USB): a simple MainWindow object is displayed with two buttons. Each time a button is pressed, a message is sent to the Arduino using a SerialPortManager object. 


Screenshot :
-------------

![Screenshot](doc/images/GBMProject3A_screenshot.jpg?raw=true "Screenshot")

At the top left corner, 2s window of raw signals updated at each time step (100 Hz in the example). 

At the top right corner, 2s window of filtered signals updated at each time step (same frequency as above).

At the bottom left corner, 2s window of raw buffered signals updated every 1s.

At the bottom right corner, Power spectrum updated for every new buffer (i.e. every 1s).

Installation :
-------------

* Either clone (git clone https://github.com/GuillaumeGibert/GBMProject3A.git using a git client) or download the project
* Upload the ino project to your Arduino
* Open the C++ project using the GBMProject3A.pro file
* Choose the example you want to run by adding it to the GBMProject3A.pro file
* Compile and Run it

Feel free to modify the code to fit your needs!

