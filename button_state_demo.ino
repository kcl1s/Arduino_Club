bool buttonState = LOW;  // Variable for reading the pushbutton status
bool oldButtonState = HIGH;  //  Variable for old button state
const int buttonPin = 5;          // button pin

void setup() {
   pinMode(buttonPin, INPUT_PULLUP);      //Easier wiring Pressed = LOW
   Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);                  //Read current button state
  if ((buttonState = LOW) && (oldButtonState = HIGH)) {   //We have a new button press
    //press code here
    Serial.println("Pressed");
     
    oldButtonState = LOW;     //update old state
  }
  else if ((buttonState = HIGH) && (oldButtonState = LOW)) {  //We have a button release
    oldButtonState = HIGH;    //update old state
  }
  delay(50);    //for button debounce
}
