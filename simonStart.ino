//button variables---
bool buttonState[] = {0, 0, 0, 0}; // Variable for reading the pushbutton status
bool oldButtonState[] = {1, 1, 1, 1}; //  Variable for old button state
const int buttonPin[] = {3, 5, 9, 11};       // button pins

//LED variables
const int LEDpins[] = {4, 6, 10, 13};        // LED pins

//random variables
const int seqLength = 30;
int sequence[seqLength];

//play variables
int playNumber = 1;
int playbackPosition = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Start serial");

  //set button pinmodes
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

  //set LED pinmodes
  for (int i = 0; i < 4; i++) {
    pinMode(LEDpins[i], OUTPUT);
  }

  //fill sequence array
  randomSeed(analogRead(0));
  for (int i = 0; i < seqLength; i++) {
    sequence[i] = random(4);
  }
}

void loop() {
  playSequence();
  int btnNumber = btnCheck();   //placeholder for button function return
}

//function to check buttons. returns -1 for no buttons or 0-3 for button pressed
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
    }
    oldButtonState[i] = buttonState[i];


  }
  delay(50);    //for button debounce
  return btnPressed;
}

void playSequence() {
  for (int i = 0; i < playNumber; i++) {

  }
}

