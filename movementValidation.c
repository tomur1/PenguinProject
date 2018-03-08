#include "movementValidation.h"

//moves penguin to a selected place if it is a valid move
int moveToDestinationAndScore(int board[sizeX][sizeY], int penguin, int selectedPenguinX, int selectedPenguinY)
{
    int destinationX,destinationY;
    int correctMove=0;
    int fish=0;
    do
    {
        printf("\nWhere do you want to put your penguin %d\n",penguin);
        scanf("%d %d",&destinationX,&destinationY);
        correctMove=checkIfValidPlaceToMove(board,destinationX,destinationY);
        if(correctMove==1)
        {
            switch (checkDirection(selectedPenguinX,selectedPenguinY,destinationX,destinationY))
            {
            case 0:     //right-up
                printf("checking right-up from the penguin\n");
                correctMove=checkRightUp(board,selectedPenguinX,selectedPenguinY,destinationX,destinationY);
                break;
            case 1:     //right
                printf("checking right from the penguin\n");
                correctMove=checkRightFlat(board,selectedPenguinX,selectedPenguinY,destinationX,destinationY);
                break;
            case 2:     //right-down
                printf("checking right-down from the penguin\n");
                correctMove=checkRightDown(board,selectedPenguinX,selectedPenguinY,destinationX,destinationY);
                break;
            case 3:     //left-down
                printf("checking left-down from the penguin\n");
                correctMove=checkLeftDown(board,selectedPenguinX,selectedPenguinY,destinationX,destinationY);
                break;
            case 4:     //left
                printf("checking left from the penguin\n");
                correctMove=checkLeftFlat(board,selectedPenguinX,selectedPenguinY,destinationX,destinationY);
                break;
            case 5:     //left-up
                printf("checking left-up from the penguin\n");
                correctMove=checkLeftUp(board,selectedPenguinX,selectedPenguinY,destinationX,destinationY);
                break;
            default:
                correctMove=0;
            }
        }
        if(!correctMove)
        {
            printf("Incorrect movement\n");
        }

    }
    while(!correctMove);
    printf("You successfully placed the penguin\n");
    fish = board[destinationX][destinationY];
    board[destinationX][destinationY]=penguin;
    board[selectedPenguinX][selectedPenguinY]=0;
    return fish;
    //store fish
    //move penguin
    //kill floe
    //return fish


}

//check in which direction the player wants to move their penguin
int checkDirection(int selectedPenguinX,int selectedPenguinY,int destinationX,int destinationY)
{
    int difference=selectedPenguinX-destinationX;
    int tempDestinationX=destinationX;
    int tempDestinationY=destinationY;

    if(selectedPenguinX%2==0 && selectedPenguinY%2==0 || selectedPenguinX%2==0 && selectedPenguinY%2==1)        //start from 1
    {
        if(difference>0)        //checking up
        {
            tempDestinationX+=1*difference;
            tempDestinationY-=1*difference/2;
            if(selectedPenguinX==tempDestinationX && selectedPenguinY==tempDestinationY)        //destination right-up
            {
                return 0;
            }
            destinationX+=1*difference;
            destinationY+=1*round_closest(difference,2);
            if(selectedPenguinX==destinationX && selectedPenguinY==destinationY)                //destination left-up
            {
                return 5;
            }

        }
        else if(difference<0)   //checking down
        {
            difference*=-1;
            tempDestinationX-=1*difference;
            tempDestinationY-=1*difference/2;
            if(selectedPenguinX==tempDestinationX && selectedPenguinY==tempDestinationY)        //destination right-down
            {
                return 2;
            }
            destinationX-=1*difference;
            destinationY+=1*round_closest(difference,2);
            if(selectedPenguinX==destinationX && selectedPenguinY==destinationY)                //destination left-down
            {
                return 3;
            }
        }
    }
    else if(selectedPenguinX%2==1 && selectedPenguinY%2==1 || selectedPenguinX%2==1 && selectedPenguinY%2==0)   //start from 2
    {
        if(difference>0)        //checking right-up
        {
            tempDestinationX+=1*difference;
            tempDestinationY-=1*round_closest(difference,2);
            if(selectedPenguinX==tempDestinationX && selectedPenguinY==tempDestinationY)        //destination right-up
            {
                return 0;
            }
            destinationX+=1*difference;
            destinationY+=1*difference/2;
            if(selectedPenguinX==destinationX && selectedPenguinY==destinationY)                //destination left-up
            {
                return 5;
            }
        }
        else if(difference<0)
        {
            difference*=-1;
            tempDestinationX-=1*difference;
            tempDestinationY-=1*round_closest(difference,2);
            if(selectedPenguinX==tempDestinationX && selectedPenguinY==tempDestinationY)        //destination right-down
            {
                return 2;
            }
            destinationX-=1*difference;
            destinationY+=1*difference/2;
            if(selectedPenguinX==destinationX && selectedPenguinY==destinationY)                //destination left-down
            {
                return 3;
            }
        }


    }
    //flat check
    if(difference==0)
    {
        if(selectedPenguinY>destinationY)       //destination is on the left
        {
            return 4;
        }
        else if(selectedPenguinY<destinationY)  //destination is on the right
        {
            return 1;
        }
    }

    return 10;  //go to default because this move is not on the path

}
int checkRightUp(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY)
{
    int i;
    int difference=selectedPenguinX-destinationX;
    if(selectedPenguinX%2==0 && selectedPenguinY%2==0 || selectedPenguinX%2==0 && selectedPenguinY%2==1)        //start from 1
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX-=1;
            if(i%2==0)
            {
                selectedPenguinY+=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }
    else if(selectedPenguinX%2==1 && selectedPenguinY%2==1 || selectedPenguinX%2==1 && selectedPenguinY%2==0)
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX-=1;
            if(i-1%2==0)
            {
                selectedPenguinY+=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }

}
int checkLeftUp(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY)
{
    int i;
    int difference=selectedPenguinX-destinationX;
    if(selectedPenguinX%2==0 && selectedPenguinY%2==0 || selectedPenguinX%2==0 && selectedPenguinY%2==1)        //start from 1
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX-=1;
            if(i-1%2==0)
            {
                selectedPenguinY-=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }
    else if(selectedPenguinX%2==1 && selectedPenguinY%2==1 || selectedPenguinX%2==1 && selectedPenguinY%2==0)
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX-=1;
            if(i%2==0)
            {
                selectedPenguinY-=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }

}
int checkRightDown(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY)
{
    int i;
    int difference=selectedPenguinX-destinationX;
    difference*=-1;
    if(selectedPenguinX%2==0 && selectedPenguinY%2==0 || selectedPenguinX%2==0 && selectedPenguinY%2==1)        //start from 1
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX+=1;
            if(i%2==0)
            {
                selectedPenguinY+=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }
    else if(selectedPenguinX%2==1 && selectedPenguinY%2==1 || selectedPenguinX%2==1 && selectedPenguinY%2==0)
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX+=1;
            if(i-1%2==0)
            {
                selectedPenguinY+=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }

}
int checkLeftDown(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY)
{
    int i;
    int difference=selectedPenguinX-destinationX;
    difference*=-1;
    if(selectedPenguinX%2==0 && selectedPenguinY%2==0 || selectedPenguinX%2==0 && selectedPenguinY%2==1)        //start from 1
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX+=1;
            if(i-1%2==0)
            {
                selectedPenguinY-=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }
    else if(selectedPenguinX%2==1 && selectedPenguinY%2==1 || selectedPenguinX%2==1 && selectedPenguinY%2==0)
    {
        for(i = 1; i < difference; i++)
        {
            selectedPenguinX+=1;
            if(i%2==0)
            {
                selectedPenguinY-=1;
            }
            if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
            {
                //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
                return 0;
            }
        }
        return 1;
    }

}
int checkRightFlat(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY)
{
    int i;
    int difference=selectedPenguinY-destinationY;
    difference*=-1;
    for(i = 0; i < difference; i++)
    {
        selectedPenguinY+=1;
        if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
        {
            //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
            return 0;
        }
    }
    return 1;

}
int checkLeftFlat(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY)
{
    int i;
    int difference=selectedPenguinY-destinationY;
    for(i = 0; i < difference; i++)
    {
        selectedPenguinY-=1;
        if(board[selectedPenguinX][selectedPenguinY]>3 || board[selectedPenguinX][selectedPenguinY]<1)
        {
            //printf("Something blocks the way on %d %d\n",selectedPenguinX,selectedPenguinY);
            return 0;
        }
    }
    return 1;

}

int checkIfValidPlaceToMove(int board[sizeX][sizeY], int x, int y)
{
    int result = 1;
    if(board[x][y]>3 || board[x][y]==0 || x>=sizeX || y>=sizeY || x<0 || y<0)
    {
        //printf("move is not valid\n");
        result = 0;
    }
    return result;
}

//checks if every penguin has no move returns 1 if so
int hasPlayerAnyMove(int board[sizeX][sizeY],int player)
{
    int i,j;
    for(i = 0; i< sizeY; i++)
    {
        for(j = 0; j<sizeX; j++)
        {
            if(board[i][j]>3)
            {
                if(decomposePlayer(board[i][j])==player)
                {
                    if(!isPenguinNeighbourhoodBlocked(board,i,j))
                    {
                        return 1;
                    }
                }
            }
        }
    }
    printf("Player %d has no possible moves\n",player);
    return 0;
}

//checks whether penguin has any move gives 1 if penguin has no move
int isPenguinNeighbourhoodBlocked(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY)
{
    int isOpen = 0;
    if(selectedPenguinX%2==0 && selectedPenguinY%2==0 || selectedPenguinX%2==0 && selectedPenguinY%2==1)        //start from 1
    {
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX-1,selectedPenguinY);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX,selectedPenguinY+1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX+1,selectedPenguinY);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX+1,selectedPenguinY-1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX,selectedPenguinY-1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX-1,selectedPenguinY-1);
        if(isOpen)
        {
            return 0;
        }
    }
    else
    {
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX-1,selectedPenguinY+1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX,selectedPenguinY+1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX+1,selectedPenguinY+1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX+1,selectedPenguinY);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX,selectedPenguinY-1);
        if(isOpen)
        {
            return 0;
        }
        isOpen=checkIfValidPlaceToMove(board,selectedPenguinX-1,selectedPenguinY);
        if(isOpen)
        {
            return 0;
        }
    }
    return 1;
}
