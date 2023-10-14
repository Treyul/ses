#include<Arduino.h>
// #include <arduino.h>
// define IR pins
#define LEFT_IR 11
#define FAR_LEFT_IR 12
#define MIDDLE_IR 10
#define RIGHT_IR 9
#define FAR_RIGHT_IR 8

// init the motor with the pin numbers
// Left motor
#define en1   7
#define in1   6
#define in2   5

// Right motor
#define en2   2
#define in3   4
#define in4   3

// define motor speed
#define pwm 100
#define pwm2 100

// var to store IR reading
int Right,Left,Middle,Far_Right,Far_Left;

// motor speed 
int pwm1 = 255;

// PID Constants
float Kp = 40;
float Ki = 0;
float Kd = 0;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

void Read_InfraRed()
{
    /*Readings interpretation
    * 0 ->  Not on line
    * 1 ->  On line
    */
  Far_Right = digitalRead(FAR_RIGHT_IR);
  Right = digitalRead(RIGHT_IR);
  Middle = digitalRead(MIDDLE_IR);
  Left = digitalRead(LEFT_IR); 
  Far_Left =digitalRead(FAR_LEFT_IR);
}

// define functions
void Line_Following();
void Stop_Motors();
void reverse(int pwm_speed);
void Move_Forward();
// void Go_right(int pwm_speed);
// void Go_left(int pwm_speed);
void U_turn();
void Move_to_the_next_Junction();
void Turn_right();
void Turn_left();
void calculate_pid();
void motor_control();
void geterr();
void Move_out_of_Junction();
// tree* Prioritize_Junction();

// tree* Prioritize_Junction();