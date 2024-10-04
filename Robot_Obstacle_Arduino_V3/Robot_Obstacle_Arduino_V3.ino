#include <Servo.h>
#include <NewPing.h>

// Definisi pin untuk motor driver (L298N)
const int LeftMotorForward = 7;     //IN3
const int LeftMotorBackward = 6;    //IN4
const int RightMotorForward = 4;    //IN1
const int RightMotorBackward = 5;   //IN2

// Pin sensor ultrasonik
#define trig_pin A1 // analog input 1
#define echo_pin A2 // analog input 2

#define maximum_distance 200 // jarak maksimal sensor ultrasonik
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); // inisialisasi sensor ultrasonik
Servo servo_motor; // inisialisasi servo

void setup() {
  // Set pin motor sebagai output
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Hubungkan servo ke pin 10
  servo_motor.attach(10);

  // Posisikan servo ke tengah
  servo_motor.write(115);
  delay(500);

  // Membaca jarak awal
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(500);

  if (distance <= 20) {  // Kondisi jika ada objek di depan
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);

    // Cek jarak ke kanan dan kiri
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    // Tentukan arah berdasarkan jarak
    if (distanceRight >= distanceLeft) {
      turnRight();
    } else {
      turnLeft();
    }

    moveStop();
  } else {
    moveForward();  // Jika tidak ada objek, maju
  }

  // Perbarui jarak
  distance = readPing();
}

// Fungsi untuk melihat ke kanan dengan servo
int lookRight() {
  servo_motor.write(50);  // Gerakkan servo ke kanan
  delay(500);
  int distance = readPing();  // Baca jarak
  delay(100);
  servo_motor.write(115);  // Kembalikan servo ke tengah
  return distance;
}

// Fungsi untuk melihat ke kiri dengan servo
int lookLeft() {
  servo_motor.write(170);  // Gerakkan servo ke kiri
  delay(500);
  int distance = readPing();  // Baca jarak
  delay(100);
  servo_motor.write(115);  // Kembalikan servo ke tengah
  return distance;
}

// Fungsi untuk membaca jarak dari sensor ultrasonik
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;  // Jika tidak ada objek, anggap jarak sangat jauh
  }
  return cm;
}

// Fungsi untuk menghentikan robot
void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

// Fungsi untuk bergerak maju
void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

// Fungsi untuk bergerak mundur
void moveBackward() {
  goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

// Fungsi untuk belok kanan
void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(500);
  moveForward();
}

// Fungsi untuk belok kiri
void turnLeft() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(500);
  moveForward();
}
