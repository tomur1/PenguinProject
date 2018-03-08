#include "boardGaneration.h"

int randomNumber(int x,int y)
{
    if(y<=x)
    {
        printf("Podano zle dane wejsciowe\n pierwsza liczba musi byc mniejsza niz druga!\n");
    }
    else
    {
        srand(time(0)+rand());
        return rand()%(y-x+1)+x;
    }
    return 0;
}

//Generates the board
void generateTheBoard(int board[sizeX][sizeY])
{
    int i,j;
    for(i = 0; i< sizeY; i++)
    {
        for(j = 0; j<sizeX; j++)
        {
            int x = randomNumber(1,3);
            board[i][j]=x;

        }
    }
}
//Draws the board
void drawTheBoard(int board[sizeX][sizeY])
{
    int i,j;
    printf("\n\n");
    for(i = 0; i < sizeY ; i++)
    {
        if(i%2==1)
        {
            printf("     ");
        }
        for(j = 0; j < sizeX ; j++)
        {
            printf("[%d,%d]=%d ",i,j,board[i][j]);
        }
        printf("\n\n");

    }
}
//A function that places the penguins on the board
void placeThePenguins(int board[sizeX][sizeY],int penguinsPerPlayer,int numberOfPlayers)
{
    int i,j;
    int x,y;
    for(i = 1; i <= penguinsPerPlayer ; i++)
    {
        for(j = 1; j <= numberOfPlayers; j++)
        {
            printf("Player %d please pick a place for your penguin nr.%d\n",j,i);
            scanf("%d %d",&x,&y);
            if(canPlacePlacement(board,x,y))
            {
                placeSinglePenguin(board,x,y,i,j);
                drawTheBoard(board);
            }
            else
            {
                printf("Please input a correct place\n");
                j--;
            }
        }
    }
}
//place a single penguin for player on coordinate [x,y]
void placeSinglePenguin(int board[sizeX][sizeY],int x,int y,int penguin,int player)
{
    //code for making different penguins
    /*
    int temp=0;
    temp=player*10;
    temp+=penguin;
    board[x][y]=temp;
    */
    board[x][y]=player*10;

}
//checks if player picked a correct place for penguin USED ONLY ON PLACEMENT PHASE
int canPlacePlacement(int board[sizeX][sizeY],int x,int y)
{
    if(board[x][y]==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//checks whether there is enouth floes left to place a penguin on
int isEnoughAvailableFloes(int board[sizeX][sizeY],int penguin,int player)
{
    int i,j,freePlaces=0;
    for(i = 0; i < sizeY ; i++)
    {
        for(j = 0; j < sizeX ; j++)
        {
            if(board[i][j]==1)
            {
                freePlaces++;
            }
        }
    }
    if(penguin*player>freePlaces)
    {
        printf("Somebody here is really unlucky, there is not enough floes for some penguins\nI recommend praying to RNGesus and trying again");
        return 0;
    }
    return 1;
}
