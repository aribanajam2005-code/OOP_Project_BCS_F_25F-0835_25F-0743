#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
//Board size 
const int TILE_SIZE = 80;
const int BOARD_SQUARES = 8;
const int WINDOW_SIZE = TILE_SIZE * BOARD_SQUARES;
//Colors for the two players
enum Color { WHITE, BLACK };
//Types of pieces
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE };
//Base class Piece all chess pieces inherit from this class
class Piece {
private:
    Color color;
    PieceType type;
    bool hasMoved;
public:
    // Constructor for set color and type
    Piece(Color c, PieceType t) {
        color = c;
        type = t;
        hasMoved = false;
    }
    virtual ~Piece() {}   // destructor 
    // Getter for color
    Color getColor() {
        return color;
    }
    // Getter for piece type
    PieceType getType() {
        return type;
    }
    // Check piece movement
    bool getMoved() {
        return hasMoved;
    }
    // Set moved flag
    void setMoved(bool val) {
        hasMoved = val;
    }
    // Returns letter symbol for the piece
    virtual char getSymbol() = 0;    //pure virtual
    //checks if a move is valid overridden by subclasses
    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) = 0;
};
// Pawn piece moves forward, captures diagonally
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c, PAWN) {}
    char getSymbol() {   // display p for pawn {
        if (getColor() == WHITE) return 'P';
        return 'p';
    }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
        int direction = -1; // White moves up (row decreases)
        int startRow = 6;
        if (getColor() == BLACK) {
            direction = 1; // Black moves down
            startRow = 1;
        }
        int rowDiff = toRow - fromRow;    //it tells how far it moves 
        int colDiff = toCol - fromCol;
        // Move one forward into empty square
        if (colDiff == 0 && rowDiff == direction) {
            if (board[toRow][toCol] == NULL)
                return true;
        }
        // Move two steps forward starting position
        if (colDiff == 0 && rowDiff == 2 * direction && fromRow == startRow) {
            if (board[toRow][toCol] == NULL && board[fromRow + direction][fromCol] == NULL)   // must be empty
                return true;
        }
        // Diagonal move 1 forward
        if (abs(colDiff) == 1 && rowDiff == direction) {
            if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != getColor())
                return true;
        }

        return false;
    }
};
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

    void handleClick(int row, int col)
    {
        if (gameOver) return;

        Piece* clicked = board.grid[row][col];

        if (!pieceSelected)
        {
            if (clicked != NULL && clicked->getColor() == currentTurn)
            {
                selectedRow = row;
                selectedCol = col;
                pieceSelected = true;
            }
            return;
        }

        if (row == selectedRow && col == selectedCol)
        {
            pieceSelected = false;
            return;
        }

        if (clicked != NULL && clicked->getColor() == currentTurn)
        {
            selectedRow = row;
            selectedCol = col;
            return;
        }

        if (isValidMoveForSelected(row, col))
        {
            Piece* moving = board.grid[selectedRow][selectedCol];
            Piece* captured = board.grid[row][col];

            board.grid[row][col] = moving;
            board.grid[selectedRow][selectedCol] = NULL;

            if (moving->getType() == KING)
            {
                if (currentTurn == WHITE) { whiteKingRow = row; whiteKingCol = col; }
                else { blackKingRow = row; blackKingCol = col; }
            }

            if (captured != NULL)
            {
                delete captured;
            }

            if (moving->getType() == PAWN)
            {
                if ((currentTurn == WHITE && row == 0) || (currentTurn == BLACK && row == 7))
                {
                    Color col2 = moving->getColor();
                    delete board.grid[row][col];
                    board.grid[row][col] = new Queen(col2);
                }
            }

            moving->setMoved(true);

            if (currentTurn == WHITE) currentTurn = BLACK;
            else currentTurn = WHITE;

            bool inCheck = isInCheck(currentTurn);
            bool hasMove = hasAnyLegalMove(currentTurn);

            if (!hasMove)
            {
                gameOver = true;
                if (inCheck)
                {
                    if (currentTurn == WHITE)
                        message = "CHECKMATE! Black wins!  (R to restart)";
                    else
                        message = "CHECKMATE! White wins!  (R to restart)";
                }
                else
                {
                    message = "STALEMATE! It's a draw!  (R to restart)";
                }
            }
            else if (inCheck)
            {
                if (currentTurn == WHITE)
                    message = "White's turn - CHECK!";
                else
                    message = "Black's turn - CHECK!";
            }
            else
            {
                if (currentTurn == WHITE)
                    message = "White's turn";
                else
                    message = "Black's turn";
            }
        }

        pieceSelected = false;
    }

    void restart()
    {
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
/// jannat 
// Draws complete chess game Gui including board, pieces , menu and status
void drawGame(sf::RenderWindow& window, Game& game, sf::Font& font)
{
    window.clear(sf::Color(30, 30, 30)); // Clear previous frame with dark background
    // Top menu bar
    sf::RectangleShape menuBar(sf::Vector2f(WINDOW_SIZE, 70));
    menuBar.setPosition(sf::Vector2f(0, 0));
    menuBar.setFillColor(sf::Color(45, 45, 45)); // dark grey strip
    window.draw(menuBar);

    // Game title
    sf::Text title(font, "CHESS GAME", 28);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(10, 5));
    window.draw(title);

    // Chess instructions
    sf::Text info(
        font,
        "P: Forward | R: Straight | B: Diagonal | N: L Shape | Q: Any Direction | K: One Step",
        14
    );

    info.setFillColor(sf::Color(220, 220, 220)); // light grey text
    info.setPosition(sf::Vector2f(10, 40));
    window.draw(info);

    Board& board = game.getBoard();


    // Draw the chessboard squares : light pink and white
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            sf::RectangleShape square(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            // position each tile in grid
            square.setPosition(sf::Vector2f(c * TILE_SIZE, r * TILE_SIZE + 70));

            // alternating colors like real chessboard
            if ((r + c) % 2 == 0)
                square.setFillColor(sf::Color(255, 255, 255));       // White
            else
                square.setFillColor(sf::Color(255, 182, 193));       // Light pink

            window.draw(square);
            // show possible move dots
            if (game.isPieceSelected() && game.isValidMoveForSelected(r, c))
            {
                if (board.grid[r][c] == NULL)
                {
                    sf::CircleShape dot(8);
                    dot.setOrigin(sf::Vector2f(8, 8)); // centres the dot properly
                    dot.setPosition(
                        sf::Vector2f(
                            c * TILE_SIZE + TILE_SIZE / 2,
                            r * TILE_SIZE + TILE_SIZE / 2 + 70
                        )
                    );
                    dot.setFillColor(sf::Color(180, 50, 50, 200));
                    window.draw(dot);
                }
            }
        }
    }
    // Now take this 2nd .cpp file here: 

    // Draw pieces (plain letters only)
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece* p = board.grid[r][c];
            if (p == NULL) continue;

            // skips empty squares
            float cx = c * TILE_SIZE + TILE_SIZE / 2.0f;
            float cy = r * TILE_SIZE + TILE_SIZE / 2.0f + 70; // convert char to string

            char sym = p->getSymbol();
            std::string symStr(1, sym);
            sf::Text text(font, symStr, 38);
            text.setStyle(sf::Text::Bold);
            text.setOutlineThickness(2); // makes the pieces visible

            // outline depends on the color of piece
            if (p->getColor() == WHITE)
                text.setOutlineColor(sf::Color::Black);
            else
                text.setOutlineColor(sf::Color::White);

            // keep pieces readable on board
            if (p->getColor() == WHITE)
                text.setFillColor(sf::Color::White);
            else
                text.setFillColor(sf::Color::Black);

            // centres the text properly on tiles
            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2,
                bounds.position.y + bounds.size.y / 2));
            text.setPosition(sf::Vector2f(cx, cy));
            window.draw(text);
        }
    }
    // Legend for chess pieces
    sf::Text legend(font,
        "P=Pawn  R=Rook  N=Knight  B=Bishop  Q=Queen  K=King",
        16);

    legend.setFillColor(sf::Color::White);
    legend.setPosition(sf::Vector2f(10, WINDOW_SIZE + 75));

    window.draw(legend);

    // Simple status bar at bottom
    sf::RectangleShape statusBar(sf::Vector2f(WINDOW_SIZE, 40));
    statusBar.setPosition(sf::Vector2f(0, WINDOW_SIZE + 100));
    statusBar.setFillColor(sf::Color(40, 40, 40));
    window.draw(statusBar);

    // Show message - includes game over info directly in status bar
    sf::Text statusText(font, game.getMessage(), 18);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(sf::Vector2f(10, WINDOW_SIZE + 110));
    window.draw(statusText);

    window.display();
    // displaying everything drawn in the frame
}

// Main function

int main()
{
    sf::RenderWindow window( // create main window for chess board and UI
        sf::VideoMode(sf::Vector2u(WINDOW_SIZE, WINDOW_SIZE + 150)),
        "Chess - OOP Project | NUCES Faisalabad"
    );
    window.setFramerateLimit(60); // smooth animation

    sf::Font font;
    bool fontLoaded = false;

    // initialize font for game text
    if (font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        fontLoaded = true;

    if (!fontLoaded)
    {
        std::cout << "Warning: Could not load font. Text may not display." << std::endl;
    }

    Game game; //main game object that handles logic

    while (window.isOpen())
    {
        while (std::optional<sf::Event> ev = window.pollEvent()) // handles event of keyboard and mouse
        {
            if (ev->is<sf::Event::Closed>())
                window.close();

            // keyboard input 
            if (const auto* key = ev->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    window.close(); // quits game

                if (key->scancode == sf::Keyboard::Scancode::R)
                    game.restart(); // restarts game
            }
            //mouse click handling
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button == sf::Mouse::Button::Left)
                {
                    // finds board square from mouse click
                    int col = click->position.x / TILE_SIZE;
                    int row = (click->position.y - 70) / TILE_SIZE;

                    // only accepts valid board inputs (clicks)
                    if (row >= 0 && row < 8 && col >= 0 && col < 8)
                        game.handleClick(row, col);
                }
            }
        }
        drawGame(window, game, font); // redraw everything
    }

    return 0;
}