bool buttonState = 0;  // Variable for reading the pushbutton status
bool oldButtonState = 1;  //  Variable for old button state
const int buttonPin = 5;          // button pin

void setup() {
   pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if ((buttonState = LOW) && (oldButtonState = HIGH)) {   //We have a new button press
    //
    //Put button press code here
    //
    oldButtonState = LOW;
  }
  else if ((buttonState = HIGH) && (oldButtonState = LOW)) {  //We have a button release
    oldButtonState = HIGH;
  }
  delay(50);    //for button debounce
}
