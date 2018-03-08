#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "boardGaneration.h"
#include "movementValidation.h"
/*
VERSION 1.1
Made by TB
*/

int sizeX,sizeY;

void playTheGame(int board[sizeX][sizeY],int scores[]);
int makeAMoveAndGiveFish(int board[sizeX][sizeY],int player);
int selectPenguin(int board[sizeX][sizeY], int player, int* selectedPenguinX, int* selectedPenguinY);
int scanBoardForPlayers(int board[sizeX][sizeY]);
int scanBoardForPenguins(int board[sizeX][sizeY]);
int decomposePlayer(int penguin);
// int decomposePenguin(int penguin);
int getSelectedPenguinX(int board[sizeX][sizeY],int penguin);
int getSelectedPenguinY(int board[sizeX][sizeY],int penguin);
unsigned int round_closest(unsigned int dividend, unsigned int divisor);
void fillScoresWithZeros(int howManyPlayersArePlaying,int scores[]);
void addScore(int currentPlayer,int scores[],int howMuchFishToAdd);
int isGameOver(int board[sizeX][sizeY]);
void gameOverScreen(int board[sizeX][sizeY], int scores[], int howManyPlayersArePlaying);


int main()
{
    printf("Hello my dear penguin\n");

    int z =randomNumber(0,4);
    printf("Random number is : %d\n",z);

    printf("Input the size of the board\n");
    scanf("%d %d",&sizeX,&sizeY);
    int board[sizeX][sizeY];


    char phase[10];
    int isPhaseWrong=1;
    do
    {


        printf("What is the game phase?\nType in 'placement' or 'movement'\n");
        scanf("%s",phase);

        if(strcmp(phase,"placement") == 0)
        {
            isPhaseWrong=0;
            int players;
            printf("How many players are playing?\n");
            scanf("%d",&players);

            int scores[players];
            fillScoresWithZeros(players,scores);

            int penguinsPerPlayer;
            printf("How many penguins per each player?\n");
            scanf("%d",&penguinsPerPlayer);

            generateTheBoard(board);
            drawTheBoard(board);
            if(!isEnoughAvailableFloes(board,penguinsPerPlayer,players))
            {

            }
            else
            {
                placeThePenguins(board,penguinsPerPlayer,players);
                playTheGame(board,scores);
            }

        }
        else if(strcmp(phase,"movement") == 0)
        {
            isPhaseWrong=0;
            printf("This section requires the readFromFile function to work");
        }
        else
        {
            printf("Please input phase correctly!\n");
        }
    }
    while(isPhaseWrong);



    return 0;

}

//the main movement function
void playTheGame(int board[sizeX][sizeY],int scores[])
{
    int gameOver=0;
    int howManyPlayersArePlaying,howManyPenguinsForPlayer;
    int currentPlayer=1;
    int howMuchFishToAdd=0;
    howManyPlayersArePlaying=scanBoardForPlayers(board);
    howManyPenguinsForPlayer=scanBoardForPenguins(board);
    printf("how many players? %d\n",howManyPlayersArePlaying);
    printf("how many penguins? %d\n",howManyPenguinsForPlayer);



    do
    {
        drawTheBoard(board);
        if(hasPlayerAnyMove(board,currentPlayer))            //if the player has an available move
        {
            howMuchFishToAdd=makeAMoveAndGiveFish(board,currentPlayer);
            addScore(currentPlayer,scores,howMuchFishToAdd);
        }
        currentPlayer=changeCurrentPlayer(currentPlayer,howManyPlayersArePlaying);
        gameOver=isGameOver(board);
    }
    while(!gameOver);
    printf("\nGame Over!\n");
    gameOverScreen(board,scores,howManyPlayersArePlaying);

}
int makeAMoveAndGiveFish(int board[sizeX][sizeY],int player)
{
    int selectedPenguinX;
    int selectedPenguinY;
    int selectedPenguin = selectPenguin(board,player,&selectedPenguinX,&selectedPenguinY);

    printf("Penguin %d is on %d %d\n",selectedPenguin,selectedPenguinX,selectedPenguinY);
    int fish = moveToDestinationAndScore(board,selectedPenguin,selectedPenguinX,selectedPenguinY);
    return fish;
}
//Select from user the penguin he wishes to move and check if the penguin belong to him
int selectPenguin(int board[sizeX][sizeY], int player, int* selectedPenguinX, int* selectedPenguinY)
{
    int x,y;
    int penguin;
    int correct=0;
    do
    {

        printf("Player %d select the penguin you wish to move\n",player);
        scanf("%d %d",&x,&y);
        if(board[x][y]>3 && player==decomposePlayer(board[x][y]))
        {
            penguin=board[x][y];
            *selectedPenguinX=x;
            *selectedPenguinY=y;
            correct=1;
        }
        else
        {
            printf("Player %d please choose correctly\n",player);
        }

    }
    while(!correct);
    return penguin;
}

//Get information from the board how many players are playing
int scanBoardForPlayers(int board[sizeX][sizeY])
{
    int i,j;
    int numberOfPlayers=0;
    int decomposedPlayer=0;
    for(i = 0; i< sizeY; i++)
    {
        for(j = 0; j<sizeX; j++)
        {
            if(board[i][j]>3)
            {
                decomposedPlayer=decomposePlayer(board[i][j]);
            }
            if(decomposedPlayer>numberOfPlayers)
            {
                numberOfPlayers=decomposedPlayer;
            }

        }
    }
    return numberOfPlayers;
}
//scan board for number of penguins for each player
int scanBoardForPenguins(int board[sizeX][sizeY])
{
    // used when each players penguins are different
    /*
    int i,j;
    int numberOfPenguins=0;
    int decomposedPenguin=0;
    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            if(board[i][j]>3)
            {
                decomposedPenguin=decomposePenguin(board[i][j]);
            }
            if(decomposedPenguin>numberOfPenguins)
            {
                numberOfPenguins=decomposedPenguin;
            }

        }
    }
    return numberOfPenguins;
    */
    int i,j;
    int numberOfPenguins=0;
    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            if(board[i][j]==10)
            {
                numberOfPenguins++;
            }

        }
    }
    return numberOfPenguins;
}
//get player from penguin
int decomposePlayer(int penguin)
{
    int temp;
    temp = penguin/10;
    return temp;
}
//get number of penguin from penguin // this should no longer be used
/*
int decomposePenguin(int penguin)
{
    int temp;
    temp=penguin%10;
    return temp;
}
*/
//checks on what X coordinate the penguins is standing
int getSelectedPenguinX(int board[sizeX][sizeY],int penguin)
{
    int i,j;
    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            if(board[i][j]==penguin)
            {
                return i;
            }
        }
    }
}
//checks on what Y coordinate the penguins is standing
int getSelectedPenguinY(int board[sizeX][sizeY],int penguin)
{
    int i,j;
    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            if(board[i][j]==penguin)
            {
                return j;
            }
        }
    }
}
//changes current player after their turn
int changeCurrentPlayer(int currentPlayer, int howManyPlayersArePlaying)
{
    if(currentPlayer==howManyPlayersArePlaying)
    {
        currentPlayer=1;
    }
    else
    {
        currentPlayer++;
    }
    return currentPlayer;
}
//rounds int up (I borrowed this function from internet)
unsigned int round_closest(unsigned int dividend, unsigned int divisor)
{
    return (dividend + (divisor / 2)) / divisor;
}
//fills score array with zeros
void fillScoresWithZeros(int howManyPlayersArePlaying,int scores[howManyPlayersArePlaying])
{
    int i;
    for(i = 0; i < howManyPlayersArePlaying; i++)
    {
        scores[i]=0;
    }
}
//Adds given number of fishes to the score of given player
void addScore(int currentPlayer,int scores[],int howMuchFishToAdd)
{
    scores[currentPlayer-1]+=howMuchFishToAdd;
    printf("Player %d has now %d fish",currentPlayer,scores[currentPlayer-1]);
}
//checks if every penguin has no move returns 1 if so

int isGameOver(int board[sizeX][sizeY])
{
    int i,j;
    for(i = 0; i< sizeY; i++)
    {
        for(j = 0; j<sizeX; j++)
        {
            if(board[i][j]>3)
            {
                if(!isPenguinNeighbourhoodBlocked(board,i,j))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
//shows the game over games stats
void gameOverScreen(int board[sizeX][sizeY], int scores[], int howManyPlayersArePlaying)
{
    drawTheBoard(board);
    int i,winner=999,maxScore=-1;;
    for(i=1; i<howManyPlayersArePlaying+1; i++)
    {
        printf("Player %d has %d fish\n",i,scores[i-1]);
        if(scores[i-1]>maxScore)
        {
            winner=i;
            maxScore=scores[i-1];
        }

    }
    printf("The Winner is Player %d with %d fish\nCongratulations!",winner,maxScore);
}

