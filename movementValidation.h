
int sizeX,sizeY;
int moveToDestinationAndScore(int board[sizeX][sizeY], int penguin, int selectedPenguinX, int selectedPenguinY);
int checkDirection(int selectedPenguinX,int selectedPenguinY,int destinationX,int destinationY);
int checkRightUp(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY);
int checkLeftUp(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY);
int checkRightDown(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY);
int checkLeftDown(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY);
int checkRightFlat(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY);
int checkLeftFlat(int board[sizeX][sizeY], int selectedPenguinX, int selectedPenguinY, int destinationX, int destinationY);
int checkIfValidPlaceToMove(int board[sizeX][sizeY], int x, int y);
int hasPlayerAnyMove(int board[sizeX][sizeY],int player);
int isPenguinNeighbourhoodBlocked(int board[sizeX][sizeY],int selectedPenguinX, int selectedPenguinY);
