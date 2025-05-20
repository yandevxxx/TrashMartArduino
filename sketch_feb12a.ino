#include <Servo.h>

// Pin definisi
#define TRIG_PIN 9
#define ECHO_PIN 8
#define SERVO_PIN 10

// Objek servo
Servo myServo;

// Konstanta jarak
const int distanceThreshold = 20; // dalam cm

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(0); // Tutup tutup tong sampah
  
  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();

  if (distance > 0 && distance < distanceThreshold) {
    // Jika jarak lebih kecil dari threshold, buka tutup
    Serial.println("Objek terdeteksi. Membuka tutup.");
    myServo.write(90); // Buka tutup
    delay(3000);       // Tunggu 3 detik
    myServo.write(0);  // Tutup kembali
  }

  delay(100); // Tunggu sebentar sebelum membaca lagi
}

// Fungsi untuk menghitung jarak
int getDistance() {
  // Kirim sinyal TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Baca sinyal ECHO
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Hitung jarak (kecepatan suara = 34300 cm/s)
  int distance = duration * 0.034 / 2;

  return distance;
}
