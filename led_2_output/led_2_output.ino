#define LedRed 2
#define LedGreen 4

void setup() {
  // put your setup code here, to run once:
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LedRed, HIGH);
  delay(1000);
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, HIGH);
  delay(1000);
  digitalWrite(LedGreen, LOW);
}
