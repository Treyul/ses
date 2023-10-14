#include"pins.h"
#include"tree.h"

void Move_Forward()
{
    analogWrite(en1,130);//fast
  analogWrite(en2,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

tree* Prioritize_Junction()
{

    /*  first update tree with all directions available  */
    current_Branch = Update_tree(current_Branch,Far_Right,Far_Left,Middle);

    /*  prioritize direction and update current branch*/
    if ( Far_Left)
    {
        Serial.println("Turn Left");
        
        Turn_left();
        current_Branch = current_Branch->Left;
    }
    else if ( Middle)
    {
        Serial.println("Moving forward");
        Move_out_of_Junction();
        Move_to_the_next_Junction();
        current_Branch = current_Branch->Foward;
    }
    else if ( Far_Right )
    {
        Serial.println("turning Right");
        Turn_right();
        current_Branch = current_Branch->Right;
    }

    return current_Branch;
}

void Move_out_of_Junction()
{
    bool Passed = false;
    Serial.print("Getting out of junction ");

    while ( !Passed )
    {

        if ( !Far_Right && !Far_Left )
        {
            Passed = true;
        }

        // Read_InfraRed();

        // Move within limits
        Line_Following();
    }

    Stop_Motors();
    // delay(2000);
}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int lms = pwm1 - PID_value;
  int rms = pwm1 + PID_value;

  // The motor speed should not exceed the max PWM value
  lms = constrain(lms, 0, 255);
  rms = constrain(rms, 0, 255);

  analogWrite(en1,lms);//fast
  analogWrite(en2,rms);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

//   Serial.print("PID_Values: ");
//   Serial.println(PID_value);
  if (lms < 160){
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
  } 
  if (rms < 160)
  {
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
  }
  
}

void Line_Following()
{  
  Read_InfraRed();
  geterr();
  calculate_pid();
  motor_control();
}

void geterr(){

if ((Far_Left == 1)&&(Left == 0) && (Middle == 0) && (Right == 0) && (Far_Right == 0))
{
    error = 5;
}
  else if ((Far_Left == 0)&&(Left == 1) && (Middle == 0) && (Right == 0) && (Far_Right == 0))
  {
    error = 2.5;
  }
  else if ((Far_Left == 0)&&(Left == 0) && (Middle == 1) && (Right == 0) && (Far_Right == 0))
  {
    error = 0;
  }
  else if ((Far_Left == 0)&&(Left == 0) && (Middle == 0) && (Right == 1) && (Far_Right == 0))
  {
    error = -2.5;
  }
  else if ((Far_Left == 0)&&(Left == 0) && (Middle == 0) && (Right == 0) && (Far_Right == 1))
  {
    error = -5;
  }
  else if (!Right && !Left && !Middle && !Far_Left && !Far_Right)
  {
    U_turn();
    current_Branch = Reverse_traversal(current_Branch);
  }
  else 
  {
    error = 0;
  }
  //  else if ((Far_Left == 0)&&(Left == 1) && (Middle == 1) && (Right == 1) && (Far_Right == 1))
  // {
  //   stop();
  //   }
//   else if ((Far_Left == 1) && (Far_Right == 0)){
//     Turn_left(); 
//   }
//   else if ((Far_Left == 0) && (Far_Right == 1)){
//     Turn_right(); 
//   }
//   else if ((Far_Left == 0)&&(Left == 0) && (Middle == 0) && (Right == 0) && (Far_Right == 0)) {
//     Stop_Motors();
//     delay(200);
//     U_turn();
//   }

}

void Stop_Motors()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void U_turn()
{
  while (!Middle)
  {
  analogWrite(en1, 130);
  analogWrite(en2,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
Read_InfraRed();
}
    // RE
//     Move_Forward();
//     delay(100);

//      while (!Far_Right)
//   {
//   analogWrite(en1,170);
//   analogWrite(en2,150);
//   digitalWrite(in1,HIGH);
//   digitalWrite(in2,LOW);
//   digitalWrite(in3,HIGH);
//   digitalWrite(in4,LOW);
//   Read_InfraRed();
//   }

//   while ( Far_Right )
//   {
//   analogWrite(en1,170);
//   analogWrite(en2,150);
//   digitalWrite(in1,HIGH);
//   digitalWrite(in2,LOW);
//   digitalWrite(in3,HIGH);
//   digitalWrite(in4,LOW);
//   Read_InfraRed();
//   }
//     while (!Right )
//   {
//   analogWrite(en1,170);
//   analogWrite(en2,150);
//   digitalWrite(in1,HIGH);
//   digitalWrite(in2,LOW);
//   digitalWrite(in3,HIGH);
//   digitalWrite(in4,LOW);
//   Read_InfraRed();
//   }

// //   retunr bot to the line
//   while (!Middle){
//     analogWrite(en1,pwm1);
//   analogWrite(en2,pwm1);
//   digitalWrite(in1,LOW);
//   digitalWrite(in2,HIGH);
//   digitalWrite(in3,LOW);
//   digitalWrite(in4,HIGH);
//   Read_InfraRed();
//   }
//     Stop_Motors();
//     delay(100);
//     // get into path following
//     geterr();
 
  }


void Turn_right()
{
    while (!Far_Left)
  {
  analogWrite(en1,170);
  analogWrite(en2,170);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }

  while ( Far_Left )
  {
  analogWrite(en1,170 );
  analogWrite(en2,170);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }
    while (! Left)
  {
  analogWrite(en1,170);
  analogWrite(en2,170);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }
  while (!Middle){
      analogWrite(en1,170);
  analogWrite(en2,170);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Read_InfraRed();

  }
  Stop_Motors();
//   delay(1700);
  geterr();
}

void Turn_left()
{
    while (!Far_Right)
  {
  analogWrite(en1,150);
  analogWrite(en2,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }

  while ( Far_Right )
  {
  analogWrite(en1,150);
  analogWrite(en2,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }
    while (!Right )
  {
  analogWrite(en1,150);
  analogWrite(en2,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }

//   retunr bot to the line
  while (!Middle){
    analogWrite(en1,pwm1);
  analogWrite(en2,pwm1);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  Read_InfraRed();
  }
    Stop_Motors();
    // delay(1300);
    // get into path following
    geterr();
}

void reverse(int pwm_speed)
{
    analogWrite(en1, pwm_speed);
    analogWrite(en2, pwm_speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

}

// void Go_Right(int pwm_speed)
// {
//     analogWrite(en1, pwm_speed);
//     analogWrite(en2, pwm_speed);
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//     digitalWrite(in3, LOW);
//     digitalWrite(in4, HIGH);
// }

// void Go_Left(int pwm_speed)
// {
//     analogWrite(en1, pwm_speed);
//     analogWrite(en2, pwm_speed);
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//     digitalWrite(in3, HIGH);
//     digitalWrite(in4, LOW);
// }

void Move_to_the_next_Junction()
{
    bool Junction = false;

    while ( !Junction )
    {

        if ( Far_Right || Far_Left )
        {
            Junction = true;       
        }
        Line_Following();
    }

    // stop the motors when a junction is reached
    Stop_Motors();
    current_Branch = Prioritize_Junction();
}

/**
 * @brief Used to prioritize turn after reching junction
 * 
 */
