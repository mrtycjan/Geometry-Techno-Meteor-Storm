#include "Entity.h"

Entity::Entity(void)
{

    ile = 30;
    speedUp = 10;

    for(int i=0; i<ile; i++)
    {
        meteor[i].setRadius(rand()%16+7);
        meteor[i].setPosition(rand()%800, (rand()%100+16)*-1);
        meteor[i].setOutlineThickness(-1.0f);
        meteor[i].setFillColor(sf::Color::Transparent);
        meteor[i].setOutlineColor(sf::Color::White);
        speed[i] = rand()%3+2;

        meteorBox[i] = meteor[i].getGlobalBounds();
    }

}
