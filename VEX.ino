#include <Vex.h>
Vex Robot;
Ultrasonic ultrasonic(6, 7);
Gyro gyro;

Adafruit_DCMotor *motorR = Robot.setMotor(4);
Adafruit_DCMotor *motorL = Robot.setMotor(2);

//float angle;


void setup() {
  Serial.begin(9600);
  Robot.begin();
  ultrasonic.begin();
  gyro.begin();
  delay(1000);
}

void loop() {
  
  // go to wall
  long distance = ultrasonic.checkUltrasonic();

  while (distance > 36) { //while the robot is more than 34cm away from an obstacle
    Robot.moveTank(motorR, motorL, -52, 52, 0.4); //move forward slowly for 0.1 seconds to corner
    distance = ultrasonic.checkUltrasonic();
  }

  //gyro turn right

  
  float current_angle = gyro.getZAngle();
  float wanted_angle = current_angle + 88; //want to do a 90deg right turn

  while (wanted_angle > current_angle) { //while not yet at angle
    Robot.moveTank(motorR, motorL, 50, 50, 0.1); //move right motor backwards and left motor forwards slowly to turn
    delay(100); //give robot time to stablilize before next gyro reading
    current_angle = gyro.getZAngle(); //update current angle to the new position
  }

  //go to rock
  while (distance > 18) { //while the robot is more than 15cm away from an obstacle
    Robot.moveTank(motorR, motorL, -52, 52, 0.4); //move forward slowly for 0.4 seconds to corner
    distance = ultrasonic.checkUltrasonic();}

  delay(10000);
  
  //go backwards to corner
  Robot.moveTank(motorR, motorL, 50, -50, 6.4); 
  
  //gyro turn right
  Robot.moveTank(motorR, motorL, 50, 50, 1.63);

  //go to start
  long newDistance = ultrasonic.checkUltrasonic();

  while (newDistance > 27) { //while the robot is more than 34cm away from an obstacle
    Robot.moveTank(motorR, motorL, -52, 52, 0.4); //move forward slowly for 0.1 seconds to corner
    newDistance = ultrasonic.checkUltrasonic();
  }

  delay(5000);

  //gyro turn to ramp

  Robot.moveTank(motorR, motorL, 50, 50, .83); //turn right

// go up ramp
  Robot.moveTank(motorR, motorL, 70, -70, 6.24);

  turnRight();
  Robot.moveTank(motorR, motorL, 65, -65, 3);

  
  Robot.end();

}


void turnRight(){
  float angle1 = gyro.getZAngle();
  float angle2 = angle1 + 80; //want to do a 90deg right turn

  while (angle2 > angle1) { //while not yet at angle
    Robot.moveTank(motorR, motorL, 50, 50, 0.2); //move right motor backwards and left motor forwards slowly to turn
    delay(100); //give robot time to stablilize before next gyro reading
    angle1 = gyro.getZAngle(); //update current angle to the new position
  }
}

void turnAround(){

  //turn 180 to face back
  Robot.moveTank(motorR, motorL, 50, -50, 1.2);
  
  float angleNow=gyro.getZAngle();
  float angleWant = angleNow + 165; 

  while (angleWant > angleNow) { //while not yet at angle
    Robot.moveTank(motorR, motorL, 50, 50, 0.2); //move right motor backwards and left motor forwards slowly to turn
    delay(100); //give robot time to stablilize before next gyro reading
    angleNow = gyro.getZAngle();
    } //update current angle to the new position
}
