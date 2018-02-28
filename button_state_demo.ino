bool buttonState = 0;  // Variable for reading the pushbutton status
bool oldButtonState = 1;  //  Variable for old button state
const int buttonPin = 5;          // button pin

void setup() {
  Serial.begin(9600);
  Serial.println("Start serial");
   pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.print(buttonState);
  Serial.println(oldButtonState);
  if ((buttonState == LOW) && (oldButtonState == HIGH)) {   //We have a new button press
    Serial.println("Pressed");
    //Put button press code here
    //
    oldButtonState = LOW;
  }
  else if ((buttonState == HIGH) && (oldButtonState == LOW)) {  //We have a button release
    oldButtonState = HIGH;
  }
  delay(500);    //for button debounce
}
