void handleClick(int row, int col) { //function runs whenever the player clicks on a square
    if (gameOver)
        return;
    Piece* clicked = board.grid[row][col];    // get piece on clicked place 
    if (!pieceSelected) {                      // if player has not selected any piece 
        if (clicked != NULL && clicked->getColor() == currentTurn) {
            selectedRow = row;
            selectedCol = col;
            pieceSelected = true;     /// store selected ppiece location
        }
        return;
    }
    if (row == selectedRow && col == selectedCol) {  // deselected the selected piece if user click it again
        pieceSelected = false;
        return;
    }
    // selected onr piece but then select another piece
    if (clicked != NULL && clicked->getColor() == currentTurn) {
        selectedRow = row;
        selectedCol = col;
        return;
    }
    // legal movment 
    if (isValidMoveForSelected(row, col)) {
        Piece* moving = board.grid[selectedRow][selectedCol];
        Piece* captured = board.grid[row][col];
        board.grid[row][col] = moving;
        board.grid[selectedRow][selectedCol] = NULL;
        //if king move change its coordinates 
        if (moving->getType() == KING) {
            if (currentTurn == WHITE) { whiteKingRow = row; whiteKingCol = col; }
            else { blackKingRow = row; blackKingCol = col; }
        }
        // if enemy piece exists remove ut 
        if (captured != NULL) {
            delete captured;
        }
        // check moe piece is pawn 
        if (moving->getType() == PAWN) {
            if ((currentTurn == WHITE && row == 0) || (currentTurn == BLACK && row == 7)) {
                Color col2 = moving->getColor();   // delete pawn and replace with queen
                delete board.grid[row][col];
                board.grid[row][col] = new Queen(col2);
            }
        }
        // pawn first 2 moves
        moving->setMoved(true);
        // switch turn of player 
        if (currentTurn == WHITE) currentTurn = BLACK;
        else currentTurn = WHITE;
        // check player id under check
        bool inCheck = isInCheck(currentTurn);
        bool hasMove = hasAnyLegalMove(currentTurn);
        // is player moves 
        if (!hasMove) {
            gameOver = true;
            if (inCheck) {
                if (currentTurn == WHITE)
                    message = "CHECKMATE! Black wins!  (R to restart)";
                else
                    message = "CHECKMATE! White wins!  (R to restart)";
            }
            else {
                message = "STALEMATE! It's a draw!  (R to restart)";
            }
        }
        else if (inCheck) {
            if (currentTurn == WHITE)
                message = "White's turn - CHECK!";
            else
                message = "Black's turn - CHECK!";
        }
        else {
            if (currentTurn == WHITE)
                message = "White's turn";
            else
                message = "Black's turn";
        }
    }

    pieceSelected = false;  // remove selection
}

void restart() {  // restart game
    board.clearBoard();
    board.setupPieces();
    currentTurn = WHITE;
    gameOver = false;
    pieceSelected = false;
    selectedRow = -1;
    selectedCol = -1;
    whiteKingRow = 7; whiteKingCol = 4;
    blackKingRow = 0; blackKingCol = 4;
    message = "White's turn";
}
};