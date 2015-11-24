#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include "Tools/Matrix.h"
#include "Filehandler/Filehandler.h"
#include "Objects/Player.h"
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
    sf::CircleShape player(50.0f);
    Player play1{10, 32, 10, 10};
    FileHandler fh{"Fieldtest1"};
    int x{0};
    int y{0};
    sf::RenderTexture off_screen;
    sf::Sprite renderSprite;
    
    sf::Clock timer{};
    sf::Time deltaTime{sf::milliseconds(2)};
    
    if(!off_screen.create(800,600))
      std::cerr << "Failed to load off_screen texture" << std::endl;
    
    sf::Sprite off_sprite(off_screen.getTexture());
    Matrix mat{};

    
    while (window.isOpen())
    {
      timer.restart();
      //cout << deltaTime.asSeconds() << endl;
      sf::Event event;
      while (window.pollEvent(event)) {
	if (event.type == sf::Event::Closed)
	  window.close();
      }
      
      
      //Player-input
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	play1.moveRight();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	play1.moveLeft();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	play1.jump();
      }
	
      //Player-update
      play1.update(fh.getMap(), static_cast<double>(deltaTime.asMilliseconds())/100);
      //Monster-update
      
      //Object-update
      
      //Camera-update
      
      //Render
	
        

      mat = fh.getArea(0,0,70,70);
      window.clear();
      for(int i{x}; i < x+32; i++) {
	for(int j{y}; j < y+32; j++) {
	  
	  if(mat.at(i,j) != 0) {
	    renderSprite.setPosition((i-x)*32, (j-y)*32);
	    renderSprite.setTexture(fh.getBlock(mat.at(i,j)));
	    window.draw(renderSprite);
	  }
	}
      }
      
      
      renderSprite.setPosition(play1.getX(), play1.getY());
      renderSprite.setTexture(fh.getBlock(1));
      window.draw(renderSprite);
      window.display();


      deltaTime = timer.getElapsedTime();
    }

    return 0;
}
