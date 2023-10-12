#include<stdio.h>
#include"tree.h"

int Right,Left,Middle,Far_Right,Far_Left;

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

int main (void)
{
    // printf("path is %i\n",path);
    printf("beginning\n");

    // create the starting point
    path = Create_branch(NULL,'S');
    current_Branch = path;
    // if (path)
        printf("true");

    // Far_Right=0;Far_Left=1;Middle=1;
    // Prioritize_Junction();
        printf("true");
    // when you meet a junction update its children
    current_Branch->Foward = Create_branch(current_Branch,'F');
    current_Branch->Left = Create_branch(current_Branch,'L');

    // current_Branch=Update_tree(current_Branch,0,1,0);
    current_Branch = current_Branch->Foward;
    current_Branch->Left = Create_branch(current_Branch,'L');

    // current_Branch=Update_tree(current_Branch,1,0,0);
    current_Branch = current_Branch->Left;
    current_Branch->Right = Create_branch(current_Branch,'R');

    current_Branch = current_Branch->Right;
    // printf("pos is %c\n",current_Branch->position);
    // printf("ppos is %c\n",current_Branch->parent->position);

    current_Branch = Reverse_traversal(current_Branch);
    // printf("beginning\n");

    // tree *tempadd =  path->Foward->Left;
    printf("%p\n",path->Left);
    printf("%p\n",path->Right);
    // printf("%p\n",tempadd);
    // printf("")
    // tree *paradd = tempadd->parent;
    // printf("%p\n%c\n%p\n",tempadd,paradd->position,path->Foward);


    // for (tree *tmp = current_Branch ; tmp != NULL; tmp = tmp->parent)
    // {
    //     printf("%c\n",tmp->position);
    // }
    // path = Finish_Start(path);
    // return 0;
}