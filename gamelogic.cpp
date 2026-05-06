
// Game class manages turns, move logic, win condition
class Game {
private:
    Board board;
    Color currentTurn;                 // tracks the turn black or white
    bool gameOver;                    // stops game 
    int selectedRow, selectedCol;          // gui logic 
    bool pieceSelected;
    int whiteKingRow, whiteKingCol;       // king position 
    int blackKingRow, blackKingCol;
    string message;

public:
    Game() {    // default constructor to initialize every value 
        currentTurn = WHITE;
        gameOver = false;
        pieceSelected = false;
        selectedRow = -1;
        selectedCol = -1;
        whiteKingRow = 7; whiteKingCol = 4;
        blackKingRow = 0; blackKingCol = 4;
        message = "White's turn";
        board.setupPieces();
    }

    Board& getBoard() { return board; }
    Color getTurn() { return currentTurn; }
    std::string getMessage() { return message; }
    int getSelectedRow() { return selectedRow; }
    int getSelectedCol() { return selectedCol; }
    bool isPieceSelected() { return pieceSelected; }
    bool isGameOver() { return gameOver; }

    bool isInCheck(Color c) {       // find that king is under check 
        int kingRow = (c == WHITE) ? whiteKingRow : blackKingRow;
        int kingCol = (c == WHITE) ? whiteKingCol : blackKingCol;
        Color enemy = (c == WHITE) ? BLACK : WHITE;
        for (int r = 0; r < 8; r++) {
            for (int col = 0; col < 8; col++) {
                Piece* p = board.grid[r][col];
                if (p != NULL && p->getColor() == enemy) {
                    if (p->isValidMove(r, col, kingRow, kingCol, board.grid))
                        return true;
                }
            }
        }
        return false;
    }
    // after moving will king be in check
    bool wouldLeaveKingInCheck(int fromRow, int fromCol, int toRow, int toCol) {
        Piece* tempGrid[8][8];  // copy board 
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                tempGrid[r][c] = board.grid[r][c];

        Piece* moving = tempGrid[fromRow][fromCol];      // the piece move 
        tempGrid[toRow][toCol] = moving;
        tempGrid[fromRow][fromCol] = NULL;

        Color moverColor = moving->getColor();
        int kingRow = (moverColor == WHITE) ? whiteKingRow : blackKingRow;  // king position 
        int kingCol = (moverColor == WHITE) ? whiteKingCol : blackKingCol;
        // if king moves
        if (moving->getType() == KING) {
            kingRow = toRow;
            kingCol = toCol;
        }
        Color enemy = (moverColor == WHITE) ? BLACK : WHITE;
        // check if king move is in danger 
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                Piece* p = tempGrid[r][c];
                if (p != NULL && p->getColor() == enemy) {
                    if (p->isValidMove(r, c, kingRow, kingCol, tempGrid))
                        return true;
                }
            }
        }
        return false;
    }
    // legal move in board 
    bool isValidMoveForSelected(int toRow, int toCol) {
        if (!pieceSelected)   // piece not selected
            return false;
        Piece* p = board.grid[selectedRow][selectedCol];
        if (p == NULL) return false;
        // validation for 8x8 grid
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
            return false;

        if (board.grid[toRow][toCol] != NULL && board.grid[toRow][toCol]->getColor() == currentTurn)
            return false;

        if (!p->isValidMove(selectedRow, selectedCol, toRow, toCol, board.grid))
            return false;

        if (wouldLeaveKingInCheck(selectedRow, selectedCol, toRow, toCol))
            return false;

        return true;
    }
    // function has valid move 
    bool hasAnyLegalMove(Color c) {
        for (int fromRow = 0; fromRow < 8; fromRow++) {
            for (int fromCol = 0; fromCol < 8; fromCol++) {
                Piece* p = board.grid[fromRow][fromCol];
                if (p == NULL || p->getColor() != c) continue;

                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        if (board.grid[toRow][toCol] != NULL && board.grid[toRow][toCol]->getColor() == c)
                            continue;
                        // check basic rules move 
                        if (!p->isValidMove(fromRow, fromCol, toRow, toCol, board.grid))
                            continue;
                        // current selected save
                        int savedSelRow = selectedRow, savedSelCol = selectedCol;
                        selectedRow = fromRow; selectedCol = fromCol;
                        // check king check 
                        bool leavesInCheck = wouldLeaveKingInCheck(fromRow, fromCol, toRow, toCol);
                        // restore original selection
                        selectedRow = savedSelRow;
                        selectedCol = savedSelCol;

                        if (!leavesInCheck)
                            return true;
                    }
                }
            }
        }
        return false;
    }
