#include"movements.h"

/**
 * @brief First step of the maze is to recognize start point 
 *  Far right and left ir are on the line
 */

void setup()
{

pinMode(LEFT_IR, INPUT);
  pinMode(MIDDLE_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(FAR_LEFT_IR, INPUT);
  pinMode(FAR_RIGHT_IR, INPUT);

  Serial.begin(9600); // Initialize Serial communication

}

void loop()
{
    // for the stop postion all irs will be on a line
      Read_InfraRed();
      Serial.println(Far_Right);
      Serial.println(Far_Left);
    if ( Far_Right && Far_Left )
    {   
        // init the tree
        path = Create_branch(NULL,'S');
        current_Branch = path;
        Move_out_of_Junction();
        // Move_to_the_next_Junction();

    }
      
      Serial.print("Here is the while value ");
      Serial.println(!Far_Left && !Far_Right && !Left && !Middle && !Right );
      if (!Far_Left && !Far_Right && !Left && !Middle && !Right)
      {
        
        Stop_Motors();
        delay(10000);
        Finish_Start(current_Branch);
        Stop_Motors();
        delay(10000);
      }
      else
      {

        Move_to_the_next_Junction();
      }
    // while ( !Far_Left && !Far_Right && !Left && !Middle && !Right );
    // {
    //   Serial.println("passed");
    //     Move_to_the_next_Junction();
    // }
}