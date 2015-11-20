#include <SFML/Graphics.hpp>
#include <iostream>
#include "Filehandler/Matrix.h"
#include "Filehandler/Filehandler.h"
#include "Objects/Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape player(50.0f);
    
    FileHandler fh{"test"};
    int x{0};
    int y{0};
    sf::RenderTexture off_screen;
    
    if(!off_screen.create(800,600))
      std::cerr << "Failed to load off_screen texture" << std::endl;
    
    sf::Sprite off_sprite(off_screen.getTexture());
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	sf::Sprite test1{fh.getBlock(5)};
	sf::Sprite test2{fh.getBlock(1)};
	
	test1.setPosition(10,10);
	test2.setPosition(10,50);
	
        
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	  x++;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	  if(x > 0)
	    x--;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	  y++;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	  if(y > 0)
	    y--;
	}

        Matrix mat = fh.getArea(0,0,60,60);
        window.clear();
	for(int i{x}; i < x+32; i++) {
	  for(int j{y}; j < y+32; j++) {
	    
	    if(mat.at(i,j) != 0) {
	      test1.setPosition((i-x)*32, (j-y)*32);
	      test1.setTexture(fh.getBlock(mat.at(i,j)));
	      window.draw(test1);
	    }
	  }
	}
	
	
	
	
        window.display();
    }

    return 0;
}
