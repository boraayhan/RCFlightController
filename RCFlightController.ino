#include <Servo.h>

#define MAX_F_ANGLE 35  //Maximum flaperon angle. Higher values are less stable but allow for more freedom of motion. Does NOT include flaps
#define FLAP_ANGLE 25

#define VRX_PIN A0
#define VRY_PIN A1
#define JBUTTON_PIN 2

double jX = 0;
double jY = 0;
int flap = 0;

Servo f1;  //Flaperon
Servo f2;
Servo elev;  //Elevon

float f1_a0 = 88;  //Calibrated zero-level for flaperons, initially manual but might add method to calibrate it midair using PID
float f2_a0 = 90;
void setup() {
  Serial.begin(9600);
  f1.attach(8);
  pinMode(JBUTTON_PIN, INPUT);
}

void loop() {
  //TestFlaperons(30);
  UpdateControls();
}

void TestFlaperons(float ang) {
  f1.write(f1_a0 - ang);
  delay(700);
  f1.write(f1_a0 + ang);
  delay(700);
}

void UpdateControls() {
  jX = constrain(analogRead(VRX_PIN) - 500, -400, 400);
  jY = constrain(analogRead(VRY_PIN) - 500, -400, 400);
  Serial.println(jX);
  //Serial.println(jY);
  f1.write(f1_a0 + jX / 400 * MAX_F_ANGLE - flap);
}