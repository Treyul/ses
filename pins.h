#include<Arduino.h>
// #include <arduino.h>
// define IR pins
#define LEFT_IR A3
#define FAR_LEFT_IR A3
#define MIDDLE A3
#define RIGHT_IR A3
#define FAR_RIGHT_IR A3

// init the motor with the pin numbers
// Left motor
#define en1   5
#define in1   1
#define in2   2

// Right motor
#define en2   0
#define in3   4
#define in4   3

// define motor speed
#define pwm 100
#define pwm2 100

// var to store IR reading
int Right,Left,Middle,Far_Right,Far_Left;

void Read_InfraRed()
{
    /*Readings interpretation
    * 0 ->  Not on line
    * 1 ->  On line
    */

  Far_Right = digitalRead(FAR_RIGHT_IR);
  Right = digitalRead(RIGHT_IR);
  Left = digitalRead(LEFT_IR); 
  Far_Left =digitalRead(FAR_LEFT_IR);
}

// define functions
void Line_Following();
void Stop_Motors();
void Move_Forward(int pwm_speed);
void Go_right(int pwm_speed);
void reverse(int pwm_speed);
void Go_left(int pwm_speed);
void Move_to_the_next_Junction();
void Prioritize_Junction();