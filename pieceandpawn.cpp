
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
//Board size 
const int TILE_SIZE = 80;
const int BOARD_SQUARES = 8;
const int WINDOW_SIZE = TILE_SIZE * BOARD_SQUARES;
//Colors for the two players
enum Color { WHITE, BLACK };
//Types of pieces
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE };
//Base class Piece all chess pieces inherit from this class
class Piece
{
private:
    Color color;
    PieceType type;
    bool hasMoved;
public:
    // Constructor for set color and type
    Piece(Color c, PieceType t)
    {
        color = c;
        type = t;
        hasMoved = false;
    }
    virtual ~Piece() {}   // destructor 
    // Getter for color
    Color getColor()
    {
        return color;
    }
    // Getter for piece type
    PieceType getType()
    {
        return type;
    }
    // Check piece movement
    bool getMoved()
    {
        return hasMoved;
    }
    // Set moved flag
    void setMoved(bool val)
    {
        hasMoved = val;
    }
    // Returns letter symbol for the piece
    virtual char getSymbol() = 0;    //pure virtual
    //checks if a move is valid overridden by subclasses
    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) = 0;
};
// Pawn piece moves forward, captures diagonally
class Pawn : public Piece
{
public:
    Pawn(Color c) : Piece(c, PAWN) {}
    char getSymbol()   // display p for pawn
    {
        if (getColor() == WHITE) return 'P';
        return 'p';
    }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8])
    {
        int direction = -1; // White moves up (row decreases)
        int startRow = 6;
        if (getColor() == BLACK)
        {
            direction = 1; // Black moves down
            startRow = 1;
        }
        int rowDiff = toRow - fromRow;    //it tells how far it moves 
        int colDiff = toCol - fromCol;
        // Move one forward into empty square
        if (colDiff == 0 && rowDiff == direction)
        {
            if (board[toRow][toCol] == NULL)
                return true;
        }
        // Move two steps forward starting position
        if (colDiff == 0 && rowDiff == 2 * direction && fromRow == startRow)
        {
            if (board[toRow][toCol] == NULL && board[fromRow + direction][fromCol] == NULL)   // must be empty
                return true;
        }
        // Diagonal move 1 forward
        if (abs(colDiff) == 1 && rowDiff == direction)
        {
            if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != getColor())
                return true;
        }

        return false;
    }
};
