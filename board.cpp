// Board class 8x8 grid of pieces
class Board {
public:
    Piece* grid[8][8];
    Board() {
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                grid[r][c] = NULL;    //just initial stage no piece 
    }
    ~Board() {
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++) {
                if (grid[r][c] != NULL) { // checks every square if piece exists delete it
                    delete grid[r][c];
                    grid[r][c] = NULL;
                }
            }
    }

    void setupPieces() {   // top black pieces 
        grid[0][0] = new Rook(BLACK);
        grid[0][1] = new Knight(BLACK);
        grid[0][2] = new Bishop(BLACK);
        grid[0][3] = new Queen(BLACK);
        grid[0][4] = new King(BLACK);
        grid[0][5] = new Bishop(BLACK);
        grid[0][6] = new Knight(BLACK);
        grid[0][7] = new Rook(BLACK);

        for (int c = 0; c < 8; c++)    // 8 pawns in row 1 
            grid[1][c] = new Pawn(BLACK);

        grid[7][0] = new Rook(WHITE);    //bottom white piece 
        grid[7][1] = new Knight(WHITE);
        grid[7][2] = new Bishop(WHITE);
        grid[7][3] = new Queen(WHITE);
        grid[7][4] = new King(WHITE);
        grid[7][5] = new Bishop(WHITE);
        grid[7][6] = new Knight(WHITE);
        grid[7][7] = new Rook(WHITE);

        for (int c = 0; c < 8; c++)  // 8 pawns in row 6
            grid[6][c] = new Pawn(WHITE);
    }

    void clearBoard() {
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++) {
                if (grid[r][c] != NULL) {
                    delete grid[r][c];
                    grid[r][c] = NULL;
                }
            }
    }
};