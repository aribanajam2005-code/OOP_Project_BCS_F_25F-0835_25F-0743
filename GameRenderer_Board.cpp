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
