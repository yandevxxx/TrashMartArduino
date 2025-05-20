#include <Servo.h>


#define TRIG_PIN 9
#define ECHO_PIN 8
#define SERVO_PIN 10

Servo myServo;

const int distanceThreshold = 20; 

void setup() 
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(0); 
  
  Serial.begin(9600);
}

void loop() 
{
  int distance = getDistance();

  if (distance > 0 && distance < distanceThreshold) 
  {
    Serial.println("Objek terdeteksi. Membuka tutup.");
    myServo.write(90);
    delay(3000);       
    myServo.write(0); 
  }

  delay(100);
}

int getDistance() 
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
