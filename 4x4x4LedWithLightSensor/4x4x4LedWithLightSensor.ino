int vertical[16] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 22, A6, A5, A4 };
int level[4] = { A3, A2, A1, A0 };
int lightPin = A7;
byte lightThreshold = 200;
bool turnedOn = true;
int lightOnForMs = 50;

/* 
  verticals
  D13, D12,   D11,   D10
  D9,   D8,   D7,    D6
  D5,   D4,   D3,    D2
  22,  A6,   A5,    A4

  levels
  A3,   A2,   A1,    A0  

  light sensor
  A7

  resistors.  oT make LED brightness not too intensive, and equal between all colors, I use 1k resistor for blue and red levels, 220 for yellow, and 10k for green
  blue, red   1k
  yellow      200
  green       10k
*/

void setup() {
  for (int i = 0; i < 16; i++) {
    pinMode(vertical[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(level[i], OUTPUT);
  }
  pinMode(lightPin, INPUT);
  randomSeed(analogRead(10));
  allOff();
}


void loop() {
  if (IsDark()) {
    flicker(1000);
  } else {
    if (turnedOn) {
      allOff();
    }
    delay(1000);
  }
}

bool IsDark() {
  int light = analogRead(lightPin);
  return light < lightThreshold ? true : false;
}

void allOff() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(vertical[i], 1);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(level[i], 0);
  }
  turnedOn = false;
}

void flicker(int duration) {
  int cycles = duration / lightOnForMs;
  for (int i = 0; i < cycles; i++) {
    int l = random(0, 4);
    int c = random(0, 16);
    flick(l, c);
  }
  turnedOn = true;
}

void flick(int l, int c) {
  digitalWrite(level[l], 1);
  digitalWrite(vertical[c], 0);
  delay(lightOnForMs);
  digitalWrite(level[l], 0);
  digitalWrite(vertical[c], 1);
}