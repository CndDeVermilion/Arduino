int pot = A0; // Deklarasi pin untuk potensiometer

void setup() {
  // Inisialisasi komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
  // Atur pin potensiometer sebagai input
  pinMode(pot, INPUT);
}

void loop() {
  // Membaca nilai analog dari potensiometer (rentang 0 - 1023)
  float nilai = analogRead(pot);
  // Mengonversi nilai analog menjadi tegangan (rentang 0 - 5V)
  float nilai_v = nilai * (5.0 / 1023.0);
  
  // Mencetak nilai analog ke Serial Monitor
  Serial.print("Nilai analog: ");
  Serial.println(nilai);
  // Mencetak nilai tegangan ke Serial Monitor
  Serial.print("Tegangan (V): ");
  Serial.println(nilai_v);
  
  // Menunggu 1 detik sebelum membaca nilai lagi
  delay(1000);
}
