bool buttonState[] = {0, 0, 0, 0}; // Variable for reading the pushbutton status
bool oldButtonState[] = {1, 1, 1, 1}; //  Variable for old button state
const int buttonPin[] = {3, 5, 9, 11};       // button pin

void setup() {
  Serial.begin(9600);
  Serial.println("Start serial");
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

void loop() {
  int btnNumber = btnCheck();
  if (btnNumber > -1) {
    Serial.print(btnNumber);
    Serial.println(" highest pressed");
  }
}

int btnCheck() {
  int btnPressed = -1;
  for (int i = 0; i < 4; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    //Serial.print(buttonState);
    //Serial.println(oldButtonState);
    if ((buttonState[i] == LOW) && (oldButtonState[i] == HIGH)) {   //We have a new button press
      //Put button press code here      
      btnPressed = i;
      //--------------------------
      oldButtonState[i] = LOW;
    }
    else if ((buttonState[i] == HIGH) && (oldButtonState[i] == LOW)) {  //We have a button release
      oldButtonState[i] = HIGH;
    }
  }
  delay(50);    //for button debounce
  return btnPressed;
}
