#include"pins.h"
#include"tree.h"


void Line_Following()
{
        // take the infra-red readings
        Read_InfraRed();

        if ( !Left && !Right || Left && Right)
        {
            Move_Forward(pwm);
        }
        else if ( Left && !Right )
        {
            //when the left ir is on the line move left 
            Go_left(pwm2);

        }
        else if ( !Left && Right )
        {
            //when the right ir is on the line move right 
            Go_right(pwm2);
        }
        else
        {
            Move_Forward(pwm);
        }
}

void Stop_Motors()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void Move_Forward(int pwm_speed)
{
    analogWrite(en1, pwm_speed);
    analogWrite(en2, pwm_speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
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

void Go_right(int pwm_speed)
{
    analogWrite(en1, pwm_speed);
    analogWrite(en2, pwm_speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void Go_left(int pwm_speed)
{
    analogWrite(en1, pwm_speed);
    analogWrite(en2, pwm_speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

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
}

/**
 * @brief Used to prioritize turn after reching junction
 * 
 */
void Prioritize_Junction()
{

    /*  first update tree with all directions available  */
    current_Branch = Update_tree(current_Branch,Far_Right,Far_Left,Middle);

    /*  prioritize direction and update current branch*/
    if ( Far_Left )
    {
        printf("Turn left");
        current_Branch = current_Branch->Left;
    }
    else if ( Middle)
    {
        printf("Moving forward");
        current_Branch = current_Branch->Foward;
    }
    else if ( Far_Right )
    {
        printf("turning right");
        current_Branch = current_Branch->Right;
    }
}