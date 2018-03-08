int sizeX,sizeY;
int randomNumber(int x,int y);
void generateTheBoard(int board[sizeX][sizeY]);
void drawTheBoard(int board[sizeX][sizeY]);
void placeThePenguins(int board[sizeX][sizeY],int penguinsPerPlayer,int numberOfPlayers);
void placeSinglePenguin(int board[sizeX][sizeY],int x,int y,int penguin,int player);
int canPlacePlacement(int board[sizeX][sizeY],int x,int y);
int isEnoughAvailableFloes(int board[sizeX][sizeY],int penguin,int player);
