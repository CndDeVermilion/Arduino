#define ON LOW
#define OFF HIGH 

// Pin untuk setiap segmen pada 7 segment display
int pinA = 12;           
int pinB = 10;
int pinC = 8;
int pinD = 7;
int pinE = 6;   
int pinF = 11;
int pinG = 9;
// Pin untuk digit ke-1 hingga ke-4
int D1 = 5;
int D2 = 2;
int D3 = 3;
int D4 = 4;
// Pin untuk buzzer dan LED
int buzzer = 13;
int led = 1; // Tambahkan pin untuk LED

// Variabel untuk mengatur interval waktu
unsigned long previousMillis = 0; 
const long interval = 1000;  // Interval 1 detik
unsigned long previousMillisDisplay = 0;
const long displayInterval = 5; // Interval 5ms untuk refresh setiap digit
unsigned long buzzerMillis = 0;
const long buzzerInterval = 100; // Interval 1 detik untuk buzzer
unsigned long ledMillis = 0; // Tambahkan variabel untuk LED
const long ledInterval = 100; // Interval 1 detik untuk LED

int minutes = 0; // Inisialisasi menit ke 1
int seconds = 30; // Inisialisasi detik ke 0
int currentDigit = 0; // Digit saat ini yang akan ditampilkan
bool buzzerOn = false; // Status buzzer menyala atau mati
bool buzzerState = false; // Status buzzer saat ini
bool ledOn = false; // Tambahkan status LED menyala atau mati
bool ledState = false; // Tambahkan status LED saat ini
unsigned long buzzerStartMillis = 0; // Waktu mulai buzzer berbunyi
unsigned long ledStartMillis = 0; // Tambahkan waktu mulai LED menyala

// Definisi pola untuk setiap angka pada 7 segment display
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
  // Mengatur pin sebagai output
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
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT); // Mengatur pin LED sebagai output

  // Mematikan semua digit, buzzer, dan LED saat awal
  digitalWrite(D1, OFF);
  digitalWrite(D2, OFF);
  digitalWrite(D3, OFF);
  digitalWrite(D4, OFF);
  digitalWrite(buzzer, LOW); // Buzzer mati awalnya
  digitalWrite(led, LOW); // LED mati awalnya
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Logika hitung mundur
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    decrementTime();
  }

  // Logika tampilan
  if (currentMillis - previousMillisDisplay >= displayInterval) {
    previousMillisDisplay = currentMillis;
    displayTime();
    currentDigit = (currentDigit + 1) % 4; // Beralih ke digit berikutnya
  }

  // Logika buzzer dan LED
  if (minutes == 0 && seconds <= 10 && seconds > 0) {
    // Buzzer dan LED berbunyi/mati setiap 1 detik ketika waktu tersisa 10 detik atau kurang
    if (currentMillis - buzzerMillis >= buzzerInterval) {
      buzzerMillis = currentMillis;
      buzzerState = !buzzerState;
      digitalWrite(buzzer, buzzerState ? HIGH : LOW); // Toggle buzzer
    }
    if (currentMillis - ledMillis >= ledInterval) {
      ledMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led, ledState ? HIGH : LOW); // Toggle LED
    }
  } else if (minutes == 0 && seconds == 0) {
    // Buzzer dan LED menyala terus selama 5 detik ketika waktu habis
    if (!buzzerOn) {
      buzzerOn = true;
      buzzerStartMillis = currentMillis;
      digitalWrite(buzzer, HIGH); // Buzzer menyala terus
    }
    if (!ledOn) {
      ledOn = true;
      ledStartMillis = currentMillis;
      digitalWrite(led, HIGH); // LED menyala terus
    }
    if (currentMillis - buzzerStartMillis >= 5000) {
      digitalWrite(buzzer, LOW); // Buzzer mati setelah 5 detik
      buzzerOn = false;
      resetTime();
    }
    if (currentMillis - ledStartMillis >= 5000) {
      digitalWrite(led, LOW); // LED mati setelah 5 detik
      ledOn = false;
      resetTime();
    }
  } else {
    digitalWrite(buzzer, LOW); // Buzzer mati
    digitalWrite(led, LOW); // LED mati
  }
}

// Fungsi untuk mengurangi waktu
void decrementTime() {
  if (seconds == 0) {
    if (minutes == 0) {
      // Waktu habis, tampilkan 0000
      displayNumber(0, D1);
      displayNumber(0, D2);
      displayNumber(0, D3);
      displayNumber(0, D4);
      return;
    }
    minutes--;
    seconds = 59;
  } else {
    seconds--;
  }
}

// Fungsi untuk mengatur ulang waktu ke 1 menit
void resetTime() {
  minutes = 1;
  seconds = 0;
}

// Fungsi untuk menampilkan waktu pada 7 segment display
void displayTime() {
  if (minutes == 0 && seconds == 0) {
    displayNumber(0, D1);
    displayNumber(0, D2);
    displayNumber(0, D3);
    displayNumber(0, D4);
  } else {
    switch (currentDigit) {
      case 0:
        displayNumber(minutes / 10, D1);
        break;
      case 1:
        displayNumber(minutes % 10, D2);
        break;
      case 2:
        displayNumber(seconds / 10, D3);
        break;
      case 3:
        displayNumber(seconds % 10, D4);
        break;
    }
  }
}

// Fungsi untuk menampilkan angka pada digit tertentu
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
