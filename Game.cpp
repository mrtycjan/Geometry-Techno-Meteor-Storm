#include "Game.h"

Game::Game(void)
{
    state = MENU;
    windowSize = sf::Vector2f(800, 600);
    winSet.antialiasingLevel = 4;
    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Geometry Techno Meteor Storm final", sf::Style::Close);
    window.setFramerateLimit(128);

    if(!font.loadFromFile("data/emulogic.ttf"))
        return;

}
void Game::runGame()
{
    while(state != END)
    {
        switch(state)
        {
        case MENU:
        {
            menu();
            break;
        }
        case ENGINE:
        {
            start();
            break;
        }
        default:
            break;
        }
    }
}

void Game::start()
{
    Engine engine(window);
    engine.runEngine();

    state = MENU;
}

void Game::menu()
{
    std::string name[] = {"Play", "Exit", "Geometry Techno\n Meteor Storm"};

    sf::Text title[2];
    sf::Text options[2];

    title[0].setColor(sf::Color::Cyan);
    title[1].setCharacterSize(37.0f);
    title[0].setCharacterSize(37.99f);

    for(int i=0; i<2; i++)
    {
        title[i].setFont(font);
        title[i].setString(name[2]);
        title[i].setPosition((windowSize.x-title[i].getGlobalBounds().width)/2, 70);

        options[i].setFont(font);
        options[i].setString(name[i]);
        options[i].setCharacterSize(20);
        options[i].setPosition((windowSize.x-options[i].getGlobalBounds().width)/2, 265+i*50);
    }

    Audio menuAudio;
    menuAudio.playMain();

    while(state == MENU)
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));
        window.setMouseCursorVisible(true);

        sf::Event event;

        while(window.pollEvent(event))
        {
            if(options[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
            {
                menuAudio.stopMain();
                state = ENGINE;
            }

            else if(options[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left || event.type == sf::Event::Closed)
            {
				state = END;
                menuAudio.stopMain();
                window.close();
            }
        }

        for(int i=0; i<2; i++)
        {
            if(options[i].getGlobalBounds().contains(mouse))
                options[i].setColor(sf::Color::Cyan);
            else
                options[i].setColor(sf::Color::White);
        }

        window.clear();

        for(int i=0; i<2; i++)
        {
            window.draw(title[i]);
            window.draw(options[i]);
        }
        window.display();
    }

}
