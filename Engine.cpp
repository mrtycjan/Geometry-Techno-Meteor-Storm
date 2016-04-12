#include "Engine.h"

Engine::Engine(sf::RenderWindow &win)
{
    srand(time(NULL));

    windowSize = sf::Vector2f(800, 600);

    crash = false;
    gameOver = false;

    stringInfo = "Lifes: ";
    stringGameOver = "Game Over.  Your Score: ";

    if(!font.loadFromFile("data/groovy.ttf"))
        return;

    info.setString(stringInfo+toString(player.lifes));
    info.setPosition(10,10);
    info.setCharacterSize(15);
    info.setFont(font);

    game_over.setString(stringGameOver+toString(player.score));
    game_over.setCharacterSize(30);
    game_over.setFont(font);

    window = &win;
    window->setMouseCursorVisible(false);
}

inline bool Engine::collision(Player &triangle, Entity &object)
{
    for(int i=0; i<object.ile; i++)
    {
       object.meteorBox[i] = object.meteor[i].getGlobalBounds();

        if(object.meteorBox[i].intersects(triangle.ship.getGlobalBounds()))
        {
           object.meteorBox[i] = object.meteor[i].getGlobalBounds();

           if((sqrt(pow(object.meteor[i].getPosition().x - triangle.ship.getPosition().x, 2)
                + pow(object.meteor[i].getPosition().y - triangle.ship.getPosition().y, 2)))
                < (object.meteor[i].getRadius() + 12))
                {
                    object.meteor[i].setOutlineColor(sf::Color::Red);
                    return true;
                }
        }
    }
    return false;
}

void Engine::meteorControl(Entity &entities, float &delta_time)
{
    for(int i=0; i<entities.ile; i++)
    {
        if(entities.meteor[i].getPosition().y >= windowSize.y)
        {
            entities.meteor[i].setPosition(rand()%(int)windowSize.x, -17);
            entities.meteor[i].setRadius(rand()%16+7);
            entities.meteor[i].setOutlineColor(white);
        }

        entities.meteor[i].move(0, entities.speedUp*entities.speed[i]*delta_time);
    }
}
void Engine::playerControl(Player *player, float &delta_time, bool pressed)
{
    sf::Vector2f vectors;
    static sf::Vector2f wektor;
    static sf::Clock clockCrash;
    static sf::Time timerCrash;

    if(player->lifes < -1)
    {
        game_over.setString(stringGameOver+toString(player->score));
        game_over.setPosition((windowSize.x-game_over.getGlobalBounds().width)/2, windowSize.y/2);
        gameOver = true;
    }

    if(crash)
    {
        player->ship.setOutlineColor(red);
        timerCrash = clockCrash.getElapsedTime();

        if(player->lifes >= 0)
            info.setString(stringInfo+toString(player->lifes));

        if(timerCrash >= sf::seconds(5))
        {
            crash = false;
            player->ship.setOutlineColor(cyan);
            clockCrash.restart();
            player->lifes -= 1;
        }
    }

    if(player->ship.getPosition().y < - 3.f)
        player->ship.setPosition(player->ship.getPosition().x, windowSize.y + 3.f);

    else if(player->ship.getPosition().y > windowSize.y + 3.f)
        player->ship.setPosition(player->ship.getPosition().x, - 3.f);

    else if(player->ship.getPosition().x > windowSize.x + 3.f)
        player->ship.setPosition(-3.f, player->ship.getPosition().y);

    else if(player->ship.getPosition().x < - 3.f)
        player->ship.setPosition(windowSize.x + 3.f, player->ship.getPosition().y);

    if(pressed)
    {
        wektor.x = std::sin((player->ship.getRotation()*M_PI) / 180.0f);
        wektor.y = -std::cos((player->ship.getRotation()*M_PI) / 180.0f);
    }

    vectors.x = wektor.x * player->velocity * delta_time;
    vectors.y = wektor.y * player->velocity * delta_time;

    player->ship.move(vectors);
}
void Engine::runEngine()
{
    sf::Clock clock;
    sf::Time timer;

    sf::Clock time;
    float delta = 0;

    volatile bool pressed = false;
    bool menu = false;

    gameAudio.playGame();

    while(!menu)
    {
        timer = clock.getElapsedTime();

        if(timer >= sf::seconds(1))
        {
            if(!gameOver)
                player.score++;

            clock.restart();
        }

        sf::Event event;

        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                gameAudio.stopGame();
                window->close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            menu = true;
            gameAudio.stopGame();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pressed)
            player.ship.rotate(player.Rotate*delta);


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed)
            player.ship.rotate(-player.Rotate*delta);


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(player.velocity < player.accLimit)
                player.velocity += player.accelerate;
            pressed = true;
        }

        else if(sf::Event::KeyReleased)
        {
            if(player.velocity > 0)
                player.velocity -= (player.speedLess*delta);

            if(event.key.code == sf::Keyboard::Up)
                pressed = false;
        }

        meteorControl(entity, delta);

        playerControl(&player, delta, pressed);

        if(!gameOver && collision(player, entity) && !crash)
            crash = true;

        window->clear();
        window->draw(info);
        window->draw(player.ship);

        if(gameOver)
        {
            window->clear();
            window->draw(game_over);
        }

        for(int i=0; i<entity.ile; i++)
            window->draw(entity.meteor[i]);

        window->display();

        delta = time.getElapsedTime().asSeconds();
        time.restart();
    }
}

inline std::string Engine::toString(int number)
{
    std::stringstream integer;
    integer<<number;

    return integer.str();
}
