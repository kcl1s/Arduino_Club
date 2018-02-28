const int seqLength = 30;
int sequence[seqLength];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int i = 0; i < seqLength; i++) {
    sequence[i] = random(4);
  }
  Serial.println("start serial");
  for (int i = 0; i < seqLength; i++) {
    Serial.println(sequence[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

