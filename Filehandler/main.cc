#include <SFML/Graphics.hpp>
#include <iostream>
#include "Matrix.h"
#include "Filehandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    FileHandler fh{"test"};

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
	
        window.clear();

        Matrix mat = fh.getArea(1,1,32,32);

	std::cout << mat.at(0,0) << std::endl;
	
	for(int i{0}; i < 32; i++) {
	  for(int j{0}; j < 32; j++) {
	    test1.setPosition(i*32, j*32);
	    test1.setTexture(fh.getBlock(mat.at(i,j)));
	    window.draw(test1);
	  }
	}
	
        window.display();
    }

    return 0;
}
