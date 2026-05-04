
// Rook - moves horizontally or vertically
class Rook : public Piece {
public:
    Rook(Color c) : Piece(c, ROOK) {}  // inhweited from piece 
    char getSymbol() {                // just dispaly how it looka
        if (getColor() == WHITE) return 'R';
        return 'r';
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
        // move in straight line row same or column same 
        if (fromRow != toRow && fromCol != toCol)
            return false;
        // Check no pieces are blocking the path  then move up down
        int rowStep = 0, colStep = 0;
        if (toRow > fromRow) rowStep = 1;
        if (toRow < fromRow) rowStep = -1;
        if (toCol > fromCol) colStep = 1;
        if (toCol < fromCol) colStep = -1;
        int r = fromRow + rowStep;
        int c = fromCol + colStep;
        while (r != toRow || c != toCol) {  // no other piece blocks its path
            if (board[r][c] != NULL)
                return false;
            r += rowStep;
            c += colStep;
        }
        return true;
    }
};

// Knight  moves in L shape, can jump over pieces
class Knight : public Piece {
public:
    Knight(Color c) : Piece(c, KNIGHT) {}  // inherited from piece 
    char getSymbol() {    // dispaly how it looks 
        if (getColor() == WHITE) return 'N';
        return 'n';
    }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);
        // L shape: 2 steps one way
        if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
            return true;

        return false;
    }
};
// Bishop moves diagonally
class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c, BISHOP) {}  // interited from piece
    char getSymbol() {// how it disply 
        if (getColor() == WHITE) return 'B';
        return 'b';
    }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);
        // Must be diagonal 
        if (rowDiff != colDiff)
            return false;
        // Check path is clear
        int rowStep = (toRow > fromRow) ? 1 : -1;
        int colStep = (toCol > fromCol) ? 1 : -1;

        int r = fromRow + rowStep;
        int c = fromCol + colStep;
        while (r != toRow || c != toCol) { // ensure no piese blocking
            if (board[r][c] != NULL)
                return false;
            r += rowStep;
            c += colStep;
        }

        return true;
    }
};
// Queen combines rook and bishop movement logic
class Queen : public Piece {
public:
    Queen(Color c) : Piece(c, QUEEN) {}
    char getSymbol() { // how it display
        if (getColor() == WHITE) return 'Q';
        return 'q';
    }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        bool straight = (fromRow == toRow || fromCol == toCol);
        bool diagonal = (rowDiff == colDiff);

        if (!straight && !diagonal)
            return false;

        // Check path is clear
        int rowStep = 0, colStep = 0;
        if (toRow > fromRow) rowStep = 1;
        if (toRow < fromRow) rowStep = -1;
        if (toCol > fromCol) colStep = 1;
        if (toCol < fromCol) colStep = -1;

        int r = fromRow + rowStep;
        int c = fromCol + colStep;

        while (r != toRow || c != toCol) {
            if (board[r][c] != NULL)
                return false;
            r += rowStep;
            c += colStep;
        }

        return true;
    }
};
// King moves one square in any direction
class King : public Piece {
public:
    King(Color c) : Piece(c, KING) {}
    char getSymbol() {  // how it dispalys
        if (getColor() == WHITE) return 'K';
        return 'k';
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        // Only one step in any direction
        if (rowDiff <= 1 && colDiff <= 1 && (rowDiff + colDiff > 0))
            return true;

        return false;
    }
};