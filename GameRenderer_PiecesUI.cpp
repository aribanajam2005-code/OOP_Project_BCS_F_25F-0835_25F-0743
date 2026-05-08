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