#include <Servo.h> 
#include "Stepper.h"
#include <SoftwareSerial.h>
#define LaserPin 8

SoftwareSerial HC06(9, 10); //HC06-TX Pin 10, HC06-RX to Arduino Pin 11

int LED = 12; //Use whatever pins you want 
int LDR = A0; //Sensor Pin to Analog A0

Servo servo_arm;
Servo servo_spring;
//Servo servo_base; // waittt this isnt a servo, Matt help plz :)

// Setting up constants for calculations
  float g = 9.81;
  float m_arm = .04;
  float h_cm = 0.0707;
  float I_arm = 0.00053;
  float r = 0.2;
  float k = 216.52;
  float unsprung_len = .1042;
//

const int stepsPerRevolution = 1000;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 7, 6, 11);

void setup() {
// put your setup code here, to run once:

  myStepper.setSpeed(5);

// Setting up servo motors
  servo_arm.attach(5);
  servo_spring.attach(3);
  //servo_base.attach(5);
  servo_arm.write(0);
  servo_spring.write(0);
  //servo_base.write(0);

  pinMode (LaserPin, OUTPUT); 
  digitalWrite (LaserPin, HIGH);
  Serial.begin(9600);
  Serial.println("setup");
//

  // For bluetooth
  HC06.begin(9600); //Baudrate 9600 , Choose your own baudrate 
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
}

void secure_catapult_arm () {
  servo_arm.write(0);   // set 0 degrees as the angle that holds arm down
}

void position_base () {

  while (HC06.available() <= 0) {
    Serial.print("Bluetooth cannot connect");
  }
  
  int index = getVal();
  Serial.println(index);
  int x = 0;
  while (x!=2){
    if (index == 88){
        int x = getVal();
        x = x - 48;
        if(x == 2){
          return;
        } else if (x==0){
          myStepper.step(1000);
        } else if (x==1){
          myStepper.step(500);
        } else if (x==3){
          myStepper.step(-500);
        } else if (x==4){
          myStepper.step(-1000);
        } 
      }
  }
  index = getVal();
  if (index == 76){
    for (int i = 1; i <=3; i++){
      
    }
  }
  index = getVal();
  if (index == 80){
    
  }






  // to create this function, we need to input/output to the camera
  // essentially, the code will be...
  
  // int head_coordinate_x = ######## // get from camera the x coordinate of head
  // while ( head_coordinate_x > ## | head_coordinate_x < -##) {   // purpose of this is to ensure head is centered in frame
  //if (head_coordinate_x >= 0) {
  //    servo_base.write(servo_base_angle + 2);  //can change step size
  //} else if (head_coordinate_x <= 0) {
  //    servo_base.write(servo_base_angle - 2);
  //}
  // int i = 0;
  // while ( i != 50){
  //   char camera_data = camera_info();
  //   i++; 
  // }


}

int getVal() {
    int result = 0;
    if (HC06.available() <= 0) return 0;
    char val = HC06.read();

    Serial.println(val);
    // while (val != '-') {
    //     val = Serial.read();
    //     if (val >= '0' && val <= '9') {
    //         result = result * 10 + (val - '0');
    //     }
    // }
    return (int)val;
}

float get_arm_angle(float d, float h) {
  float desired_V = d * sqrt(g/(d-h)); // necessary velocity from kinematics
  float displacement = sqrt(((2*m_arm*g*h_cm+I_arm*pow(desired_V/r,2))/k)); // calculated displacement necessary from conservation of energy
  float total_extended_len = displacement + unsprung_len; //triangle side
  float theta = acos((pow(r,2)+pow(unsprung_len,2)-pow(total_extended_len,2))/(2*r*.1425)); //law of cosines gives angle in radians
  Serial.print(theta*180/3.141592);
  return 2*theta*180/3.141592;
}

void position_arm(int arm_angle) {
  servo_spring.write(arm_angle);   // change arm angle name to whatever it was named in the get_arm_angle function
}

void release_arm () {
  servo_arm.write(180);
  delay(5000);
  servo_spring.write(0);
}

char camera_info () {
  // For the Bluetooth module
  char receive;
  if(HC06.available() > 0) //When HC06 receive something
  {
    char receive = HC06.read(); //Read from Serial Communication
    Serial.println(receive);
  }
  return receive;
}

void loop() {
  // put your main code here, to run repeatedly:
  int h = 0;
  int d = 3;

  
  //myStepper.step(stepsPerRevolution);
  //delay(500);
  Serial.println("counterclockwise");
  //myStepper.step(-stepsPerRevolution);
  //delay(500);

  secure_catapult_arm();
  delay(3000);
  Serial.println("loop");
  position_base();
  delay(1000);
  int arm_angle = get_arm_angle(d, h);
  position_arm(arm_angle);
  delay(3000);
  release_arm();
  delay(1000);

}
