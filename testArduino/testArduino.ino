const int _nbPinIn = 5;
const int _portBaud = 9600;
const float _fps = 10.0;

void setup() 
{
  // initializes serial port
  Serial.begin(_portBaud);
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

    // estimates the loop duration and waits before starting a new loop
    unsigned long currentTime = micros(); // in microseconds
    unsigned long elapsedTime = currentTime - startTime; // in microseconds
    unsigned long waitingTime = 1000000/_fps - elapsedTime; // in microseconds

    if (waitingTime < 16384) //(see https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/)
      delayMicroseconds(waitingTime); // in microseconds
    else
      delay(waitingTime / 1000); // in milliseconds 
 
}
