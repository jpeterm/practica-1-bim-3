#include <Adafruit_NeoPixel.h>
 
#define trig 4
#define echo 3
#define neo 2
#define num 12
 
Adafruit_NeoPixel pixels(num, neo, NEO_GRB + NEO_KHZ800);
 
int count = 0;
const int maxPeople = 9;

const int segmentPins[] = {5, 6, 7, 8, 9, 10, 11};

const int digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 0},  {1, 1, 0, 1, 1, 0, 1}, {1, 1, 1, 1, 0, 0, 1}, {0, 1, 1, 0, 0, 1, 1},  {1, 0, 1, 1, 0, 1, 1},  {1, 0, 1, 1, 1, 1, 1},  {1, 1, 1, 0, 0, 0, 0},{1, 1, 1, 1, 1, 1, 1},  {1, 1, 1, 1, 0, 1, 1}  
};
 
void setup() {
  Serial.begin(9600);
 
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
 
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
 
  pixels.begin();
  pixels.show(); 
 
  displaydigitos(count);
}
 
void loop() {
  float distance = distancia();
 
  if (distance >= 6.0 && distance <= 10.0) {
    if (count < maxPeople) {
      count++;
      displaydigitos(count);
       for(int i =0; i<12; i++)
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); 
    } else {
      displaylleno();
      for(int i =0; i<12; i++)
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 
    }
    pixels.show();
    delay(1000); 
  }
 
  delay(100); 
}

void displaydigitos(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[digit][i]);
  }
}
 
void displaylleno() {
  for (int i = 0; i < 7; i++) {
    if (i == 6) { 
      digitalWrite(segmentPins[i], HIGH);
    } else {
      digitalWrite(segmentPins[i], LOW);
    }
  }
}

 
float distancia() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  long duration = pulseIn(echo, HIGH);
 
  float distance = (duration * 0.034) / 2;
 
  return distance;
}
