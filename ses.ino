#include"movements.h"

/**
 * @brief First step of the maze is to recognize start point 
 *  Far right and left ir are on the line
 */

void setup()
{

    if ( Far_Right && Far_Left )
    {   
        // init the tree
        path = Create_branch(NULL,'S');
        current_Branch = path;
        Move_to_the_next_Junction();
    }
}

void loop()
{

}