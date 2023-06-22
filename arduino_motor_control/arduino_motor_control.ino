#include <AFMotor.h>

#define MOTOR_SPEED 50
#define MOTOR_STEP 200
#define DELAY 2000 // milliseconds

// Number of steps per output rotation
// Change this as per your motor's specification
const int stepsPerRevolution = 200;

// connect motor to port #2 (M3 and M4)
AF_Stepper motor(stepsPerRevolution, 2);


void serial_flush();

void setup() {
  Serial.begin(9600);
  motor.setSpeed(MOTOR_SPEED);  // 50 rpm   
}

void loop() {

  if(Serial.available()) {
    motor.step(MOTOR_STEP, FORWARD, SINGLE);
    delay(DELAY);
    serial_flush();
  }
    
}

void serial_flush() {
  while(Serial.available()) Serial.read();
}
