//button variables---
bool buttonState[] = {0, 0, 0, 0}; // Variable for reading the pushbutton status
bool oldButtonState[] = {1, 1, 1, 1}; //  Variable for old button state
const int buttonPin[] = {3, 5, 9, 11};       // button pins
int btnNumber;                             // holds number returned from btnCheck

//LED variables
const int LEDpins[] = {4, 6, 10, 12};        // LED pins

//tone and light play variables
const int tonePin = 8;                  //piezo digital pin
const int delayLength = 400;            //on time for LEDs and sound
const int delayBetween = 100;           //time between lights/sounds
const int roundDelay = 2000;            //time before the next round starts

//random variables
const int seqLength = 5;               //number of rounds
int sequence[seqLength];                //array to hold the random position for each round

//play variables
int playNumber = 0;               //our position (round) number
int playbackPosition = 0;         //our button read back position
int gameState = 0;                //game state variable
const int showSequence = 0;       //our 5 states in words for easier coding
const int readInput = 1;
const int winGame = 2;
const int loseGame = 3;
const int gameOver = 4;

//Sounds variable
int sounds[] = {100, 200, 300, 400};    //array for tone pitches

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
  switch (gameState) {
    case showSequence :                  //computers turn
      Serial.print("playNumber "); Serial.println(playNumber);
      for (int i = 0; i <= playNumber; i++) {
        lightSound(sequence[i]); //pass 0 - 3
        Serial.print(sequence[i]); Serial.print(" show sequence "); Serial.println(i);
      }
      gameState = readInput;
      break;

    case readInput :                    //players turn
      btnNumber = btnCheck();
      if (btnNumber >= 0) {             //do we have a button press
        Serial.print("button # "); Serial.println(btnNumber);
        if (sequence[playbackPosition] == btnNumber) {  //is seq position the right 0 - 3
          lightSound(btnNumber);
          playbackPosition++;
          if (playbackPosition > (seqLength - 1)) {   //you made it to the end
            gameState = winGame;
            break;
          }
          if (playbackPosition > playNumber) {    //if we push all the right buttons
            gameState = showSequence;             //move to next round
            playNumber++;                         //and increase number of plays
            playbackPosition = 0;                 //reset pbp to 0 for new round
            delay(roundDelay);                    //delay before starting next round
          }
        }
        else {                          //wrong button pressed
          gameState = loseGame;
          break;
        }
      }
      break;

    case winGame :
      //win code here
      Serial.println("You Win");
      gameState = gameOver;
      break;

    case loseGame :
      //lose code here
      Serial.print("You Lose");
      gameState = gameOver;
      break;

    case gameOver :
      //do nothing
      break;
  }
}

//function to check buttons. returns -1 for no buttons or 0-3 for button pressed
int btnCheck() {
  int btnPressed = -1;
  for (int i = 0; i < 4; i++) {                   //loop through 4 buttons (0 - 3)
    buttonState[i] = digitalRead(buttonPin[i]);
    if ((buttonState[i] == LOW) && (oldButtonState[i] == HIGH)) {   //We have a new button press
      btnPressed = i;                                               //note its number
    }
    oldButtonState[i] = buttonState[i];       //keep track of last button state
  }
  delay(50);    //for button debounce
  return btnPressed;                        //return button number (0 - 3) or -1 for no press
}

//function to make light and sound for play step
void lightSound(int spot) {   // which spot on game 0 - 3
  digitalWrite(LEDpins[spot], HIGH);      //turn on light
  tone(tonePin, sounds[spot]);            //and sound
  if (gameState == readInput) {                 //check for Input gamestate
    for (int i = 0; i < delayLength; i++) {     //loop to check button state
      delay(1);                                 //every one millisecond
      if (digitalRead(buttonPin[spot])) break;  //break if button released
    }
  }
  else delay(delayLength);      //if show sequence mode use delay length

  digitalWrite(LEDpins[spot], LOW);       //turn off light
  noTone(tonePin);                        //and sound
  delay(delayBetween);        //delay between sequence
}


