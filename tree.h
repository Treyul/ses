#include<stdlib.h>
// int Right,Left,Middle,Far_Right,Far_Left;

// #include"movements.h"
/**
 * the tree is only updated when a junction is met
 * Each branch in a tree is a junction
 */

typedef struct tree
{
    char position;

    // init mem addresses
    struct tree *Left;
    struct tree *Foward;
    struct tree *Right;
    struct tree *parent;

}tree;

// used to created the branches used to store movements
tree* Create_branch(struct tree *current,char movement)
{
    // create memory to store the values of the branch
    tree* tmp = (struct tree*)malloc(sizeof(struct tree));

    // assign values to the memory slots created
    tmp->position=movement;
    tmp->Foward=NULL;
    tmp->Left=NULL;
    tmp->Right=NULL;
    tmp->parent=current;

    // return the created branch
    return tmp;
}

/**
 * @brief create branches of the junction and update the tree, take IR redaings as args
 * 
 * @param current ir
 * @param right ir
 * @param left ir
 * @param middle ir
 * @return tree* 
 */
tree *Update_tree(tree* current,int right, int left, int middle)
{

    // create the branches to store the data
    if (right)
    {
        current->Right = Create_branch(current,'R');
    }
    if (left)
    {
        current->Left = Create_branch(current,'L');
    }
    if (middle)
    {
        current->Foward = Create_branch(current,'F');
    }

    return current;
}

tree* Delete_children(tree *current)
{
    free(current->Foward);
    free(current->Left);
    free(current->Right );
}

// get to the nearest junctions that all branches are not dead ends
/**
 * @brief  reverse the current
 * 
 * @param current_branch 
 * @return tree* 
 */
tree* Reverse_traversal (tree* current_branch)
{
    tree *tmp = current_branch;
    char side = tmp->position;
    
    Serial.println("END..U-turn..moving to previous junction\n");
    // create a loop where it reaches to a junction with at least one posibility to join the branch
    /**
     * @brief first get the parent to see if it has more than one junction
     * @brief Loop
     */
    while(tmp->Left == NULL && tmp->Right == NULL && tmp->Foward == NULL)
    {
        // check direction movement
        if ( tmp->position == 'L' )
        {

            if (tmp->parent->Foward || tmp->parent->Right)
            {
                break;
            }
            // Serial.println("turn right\n");
            Turn_right();
            // Serial.println("moving to next prev junction\n");
            Move_to_the_next_Junction();
            tmp = tmp->parent;
            tmp->Left = NULL;
            free(tmp->Left);
            // Serial.println("%c",tmp->position);
            
        }
        else if ( tmp-> position == 'R')
        {
            if (tmp->parent->Foward || tmp->parent->Left)
            {
                break;
            }
            // Serial.println("turn left\n");
            Turn_left();
            Serial.println("moving to next prev junction\n");
            Move_to_the_next_Junction();
            tmp = tmp->parent;
            tmp->Right =NULL;
            free(tmp->Right);
            // Serial.println("%c",tmp->position);
        }
        else 
        {
            if (tmp->parent->Right || tmp->parent->Left)
            {
                break;
            }

            // Serial.println("moving forward\n");
            // Serial.println("moving to next prev junction\n");
            Move_out_of_Junction();
            Move_to_the_next_Junction();
            tmp = tmp->parent;
            tmp->Foward =NULL;
            free(tmp->Foward);
            // Serial.println("%c",tmp->position);
        }
    }
    // check the directional value of the branch
    // Serial.println("\nreached!!! \npos is %c\n",tmp->position);

    // Return to noraml maze traversion 
    // check the orientation
    if ( tmp->position == 'L' )
    {
        // check the other junctions available to be confirmed by ir of their existence
        if( tmp->parent->Foward != NULL)
        {
            Serial.println("Turn left...\n");
            Turn_left();
            tmp = tmp->parent->Foward;
        }
        else if ( tmp->parent->Right != NULL )
        {
            Serial.println("Move Forward...\n");
           Move_out_of_Junction();
        //    Move_to_the_next_Junction();
            tmp = tmp->parent->Right;
        }
    }
    else if ( tmp->position == 'F' )
    {
        if (  tmp->parent->Left )
        {
            Serial.println("Turn left \n");
            Turn_left();
            tmp = tmp->parent->Right;
        }
        else if (  tmp->parent->Left )
        {
            Serial.println("turn right\n");
            Turn_right();
            tmp = tmp->parent->Left;
        }
    }
    else if ( tmp->position == 'R' )
    {
        if ( tmp->parent->Left )
        {
            Serial.println("Move forward\n");
            Move_out_of_Junction();
            // Move_to_the_next_Junction();
            tmp = tmp->parent->Left;
        }
        else if ( tmp->parent->Foward)
        {
            Serial.println("Turn Right\n");
            Turn_right();
            tmp = tmp->parent->Foward;
        }
    }

    return tmp;
}


tree * Finish_Start(tree* current)
{
    for (current; current !=NULL; current=current->parent)
    {
        if ( current->position == 'L' )
        {
            printf("turn right\n");
            printf("moving to the next junction\n");
            // current = current->parent;
        }
        else if ( current-> position == 'R')
        {
            printf("turn left\n");
            printf("moving to the next junction\n");
            // current = current->parent;
        }
        else 
        {
            printf("move forward\n");
            printf("moving to the next junction\n");
            // current = current->parent;
        }
    }
}


// The root of the tree
tree* path;
// branch used for the traversion and tree update
tree *current_Branch;