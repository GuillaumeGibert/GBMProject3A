const int _nbPinIn = 5;
const int _portBaud = 9600;
const float _fps = 10.0;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() 
{
  // initializes serial port
  Serial.begin(_portBaud);

  // reserves 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() 
{
    // initialzes the timer
    unsigned long startTime = micros();

    
    Serial.print("Sensor:|");
  
    for (int l_pinIn = 0; l_pinIn < _nbPinIn; l_pinIn++)
    {
        //reads data once (and discards it) to avoid wrong estimation
        analogRead(l_pinIn);

        // writes values on the serial port
        Serial.print(analogRead(l_pinIn)); Serial.print("|");
    }

    Serial.print("\n");


    // print the string when a newline arrives:
    if (stringComplete) 
    {
      Serial.println(inputString);
      // clear the string:
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
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
