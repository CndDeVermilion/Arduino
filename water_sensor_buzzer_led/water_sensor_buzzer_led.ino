// Pin untuk modul water test
int waterSensor = A0; // Sesuaikan dengan pin yang digunakan untuk modul water test
// Pin untuk LED dan buzzer
int ledPin = 7;
int buzzerPin = 8;

// Variabel untuk interval waktu LED dan buzzer
unsigned long previousMillis = 0;
const long interval = 100; // Interval 100ms untuk kedip LED dan bunyi buzzer

// Variabel status LED dan buzzer
bool ledState = false;
bool buzzerState = false;

void setup() {
  // Mengatur pin sebagai input atau output
  pinMode(waterSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Mematikan LED dan buzzer saat awal
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // Membaca nilai dari sensor air
  int sensorValue = analogRead(waterSensor);

  // Jika air terdeteksi (nilai sensor lebih besar dari threshold)
  if (sensorValue > 500) { // Sesuaikan threshold dengan kondisi sensor
    unsigned long currentMillis = millis();

    // Toggle LED dan buzzer setiap interval 100ms
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      buzzerState = !buzzerState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
      digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
    }
  } else {
    // Jika tidak ada air, matikan LED dan buzzer
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}
