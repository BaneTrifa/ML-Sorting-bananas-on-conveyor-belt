#include <Servo.h>

char command;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(3);
}


void loop() {

  if(Serial.available()) {
    command = Serial.read();

    switch(command) {
      case 'R':
        servo.write(45);
        break;
      case 'V':
        servo.write(90);
        break;
      case 'O':
        servo.write(90);
        break;
      default:
        servo.write(150);
    }
    
  }
}

