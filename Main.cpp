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