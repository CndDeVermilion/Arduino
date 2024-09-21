#define ON LOW
#define OFF HIGH 

int pinA = 12;           
int pinB = 10;
int pinC = 8;
int pinD = 7;
int pinE = 6;   
int pinF = 11;
int pinG = 9;
int D1 = 5;
int D2 = 2;
int D3 = 3;
int D4 = 4;

unsigned long previousMillis = 0; 
const long interval = 500;  // interval 500ms

int startNumber = 1;
int currentDigit = 0;

const int segments[10][7] = {
  {OFF, OFF, OFF, OFF, OFF, OFF, ON},  // 0
  {ON, OFF, OFF, ON, ON, ON, ON},      // 1
  {OFF, OFF, ON, OFF, OFF, ON, OFF},   // 2
  {OFF, OFF, OFF, OFF, ON, ON, OFF},   // 3
  {ON, OFF, OFF, ON, ON, OFF, OFF},    // 4
  {OFF, ON, OFF, OFF, ON, OFF, OFF},   // 5
  {OFF, ON, OFF, OFF, OFF, OFF, OFF},  // 6
  {OFF, OFF, OFF, ON, ON, ON, ON},     // 7
  {OFF, OFF, OFF, OFF, OFF, OFF, OFF}, // 8
  {OFF, OFF, OFF, OFF, ON, OFF, OFF}   // 9
};

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, OFF);
  digitalWrite(D2, OFF);
  digitalWrite(D3, OFF);
  digitalWrite(D4, OFF);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    incrementStartNumber();
  }
  
  displayNumbers();
}

void incrementStartNumber() {
  startNumber++;
  if (startNumber > 9) {
    startNumber = 0;
  }
}

void displayNumbers() {
  displayNumber((startNumber + 0) % 10, D1);
  delay(1);
  displayNumber((startNumber + 1) % 10, D2);
  delay(1);
  displayNumber((startNumber + 2) % 10, D3);
  delay(1);
  displayNumber((startNumber + 3) % 10, D4);
  delay(1);
}

void displayNumber(int num, int digit) {
  digitalWrite(D1, digit == D1 ? ON : OFF);
  digitalWrite(D2, digit == D2 ? ON : OFF);
  digitalWrite(D3, digit == D3 ? ON : OFF);
  digitalWrite(D4, digit == D4 ? ON : OFF);

  digitalWrite(pinA, segments[num][0]);
  digitalWrite(pinB, segments[num][1]);
  digitalWrite(pinC, segments[num][2]);
  digitalWrite(pinD, segments[num][3]);
  digitalWrite(pinE, segments[num][4]);
  digitalWrite(pinF, segments[num][5]);
  digitalWrite(pinG, segments[num][6]);
}
