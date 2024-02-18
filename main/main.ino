#include <Servo.h> 

Servo servo_arm;
Servo servo_spring;
Servo servo_base;

void setup() {
// put your setup code here, to run once:


// Setting up constants for calculations
  servo_arm.attach(3);
  servo_spring.attach(4);
  servo_base.attach(5);
  servo_arm.write(0);
  servo_spring.write(0);
  servo_base.write(0);
  float g = 9.81;
  float m_arm = .04;
  float h_cm = 0.0707;
  float I_am


  
//


}

void secure_catapult_arm () {
  servo_arm.write(0);   // set 0 degrees as the angle that holds arm down
}

void position_base () {
  // to create this function, we need to input/output to the camera
  // essentially, the code will be...
  
  // int head_coordinate_x = ######## // get from camera the x coordinate of head
  // while ( head_coordinate_x > ## | head_coordinate_x < -##) {   // purpose of this is to ensure head is centered in frame
  //if (head_coordinate_x >= 0) {
  //    servo_base.write(servo_base_angle + 2);  //can change step size
  //} else if (head_coordinate_x <= 0) {
  //    servo_base.write(servo_base_angle - 2);
  //}
}


int get_arm_angle() {


}

void position_arm(int arm_angle) {
  servo_spring.write(arm_angle);   // change arm angle name to whatever it was named in the get_arm_angle function
}

void release_arm () {
  servo_arm.write(180);
}



void loop() {
  // put your main code here, to run repeatedly:

}
