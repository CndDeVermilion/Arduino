#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define HEART_SENSOR_PIN A0
#define RED_LED_PIN 9
#define GREEN_LED_PIN 10
#define POT_PIN A1 // Pin untuk membaca potensiometer

// Display Definitions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

int heartRate; // To store heart rate
int sensorValue; // To store sensor reading
int threshold = 10; // Threshold for detecting valid heartbeat signal
int potValue; // Nilai potensiometer

void setup() {
  // Initialize the Serial
  Serial.begin(9600);

  // Initialize the OLED display
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println("PendeteksiDetak Jantung");
  oled.display();

  // Initialize the LCD display
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Detak Jantung:");

  // Initialize LEDs
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Initialize Heart Sensor
  pinMode(HEART_SENSOR_PIN, INPUT);
}

void loop() {
  // Baca nilai potensiometer
  potValue = analogRead(POT_PIN);
  int sensorPower = map(potValue, 0, 1023, 0, 255);

  if (sensorPower > 100) { // Pastikan sensor mendapat cukup tegangan
    // Baca nilai sensor
    sensorValue = analogRead(HEART_SENSOR_PIN);

    if (sensorValue > threshold) { // Cek apakah sensor mendeteksi detak jantung
      heartRate = map(sensorValue, 0, 1023, 60, 100); // Konversi sederhana

      // Kontrol LED berdasarkan detak jantung
      if (heartRate > 80) {
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, LOW);
      } else {
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, HIGH);
      }

      // Perbarui LCD dengan detak jantung
      lcd.setCursor(0, 1);
      lcd.print("Detak: ");
      lcd.print(heartRate);
      lcd.print(" BPM   "); // BPM: Beats Per Minute (Detak Per Menit)

      // Perbarui OLED
      oled.clearDisplay();
      oled.setCursor(0, 0);
      oled.print("Heart Rate:");
      oled.setCursor(0, 20);
      oled.setTextSize(2);
      oled.print(heartRate);
      oled.print(" BPM");
      oled.display();

      // Cetak ke Serial Monitor (opsional)
      Serial.print("Detak Jantung: ");
      Serial.print(heartRate);
      Serial.println(" BPM");

    } else { // Tidak ada sinyal yang valid terdeteksi
      // Tampilkan pesan "Silahkan tempelkan jari di sensor" di LCD
      lcd.setCursor(0, 1);
      lcd.print("Silahkan tempelkan");
      lcd.setCursor(0, 2);
      lcd.print("jari di sensor  ");

      // Perbarui OLED dengan pesan default
      oled.clearDisplay();
      oled.setCursor(0, 0);
      oled.print("Sedang Scan");
      oled.display();

      // Nyalakan kedua LED ketika tidak ada sinyal yang terdeteksi
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
    }
  } else { // Sensor tidak aktif karena potensiometer
    // Matikan LED dan tampilkan pesan di LCD dan OLED
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Sensor Mati        ");

    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.print("--HIMTEK--");
    oled.display();
  }

  delay(1000); // Tunda selama 1 detik
}
