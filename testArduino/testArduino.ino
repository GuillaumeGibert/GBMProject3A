#include <SoftwareSerial.h> // for Bluetooth communication with HC05 (or HC06) module
#define rxPin 0 // arduino pin 11 as RX, connect to HC-05 TX pin 
#define txPin 1 // arduino pin 10 as TX, connect to HC-05 RX pin
SoftwareSerial virtualSerial(rxPin, txPin); //virtual serial communication port

const int _nbPinIn = 5; // number of analog inputs to read
const int _portBaud = 9600; // baud rate of the serial port
const float _fps = 10.0; // frame rate to send data
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() 
{
  // initializes the serial port
  Serial.begin(_portBaud);

  // initializes the virtual serial port for Bluetooth communication
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   virtualSerial.begin(_portBaud);

  // reserves 200 bytes for the inputString:
  inputString.reserve(200);

  // initializes the builtin led as an output
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() 
{
    // initialzes the timer
    unsigned long startTime = micros();

    Serial.print("Sensor:|"); // writes on the serial port
    virtualSerial.print("Sensor:|"); //writes on Bluetooth
    
    for (int l_pinIn = 0; l_pinIn < _nbPinIn; l_pinIn++)
    {
        //reads data once (and discards it) to avoid wrong estimation
        analogRead(l_pinIn);

        // writes values on the serial port
        Serial.print(analogRead(l_pinIn)); Serial.print("|");
        
        // writes values on the virtual serial port (Bluetooth)
        virtualSerial.print(analogRead(l_pinIn)); virtualSerial.print("|");
    }

    Serial.print("\n"); // writes on the serial port
    virtualSerial.print("\n"); //writes on Bluetooth


    // prints the string when a newline arrives:
    if (stringComplete) 
    {
      if (inputString.equals("Start\n"))
        digitalWrite(LED_BUILTIN, HIGH);

      if (inputString.equals("Stop\n"))
        digitalWrite(LED_BUILTIN, LOW);
      
      // clears the string:
      inputString = "";
      stringComplete = false;
    }

    // estimates the loop duration and waits before starting a new loop
    unsigned long currentTime = micros(); // in microseconds
    unsigned long elapsedTime = currentTime - startTime; // in microseconds
    unsigned long waitingTime = 1000000/_fps - elapsedTime; // in microseconds

    if (waitingTime < 16384) //(see https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/)
      delayMicroseconds(waitingTime); // in microseconds
    else
      delay(waitingTime / 1000); // in milliseconds 
 
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() 
{
  while (Serial.available()) 
  {
    // gets the new byte:
    char inChar = (char)Serial.read();
    // adds it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // does something about it:
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
  }
}
