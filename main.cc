#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include "Tools/Matrix.h"
#include "Filehandler/Filehandler.h"
#include "Objects/Player.h"
#include "Objects/Monster.h"
#include "Graphics/Camera.h"

using namespace std;

int main()
{
  sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
  sf::CircleShape player(50.0f);
  Player play1{10, 320, 10, 10};
  FileHandler fh{"Fieldtest1"};
  int x{0};
  int y{0};
    
  sf::Sprite renderSprite;
  sf::Sprite playerSprite;
  sf::Clock timer{};
  sf::Time deltaTime{sf::milliseconds(2)};
    
  sf::RenderTexture off_screen;
    
  if(!off_screen.create(256*32, 256*32))
    std::cerr << "Failed to load off_screen texture" << std::endl;

  for(int i{0}; i < 256; i++) {
    for(int j{0}; j < 256; j++) {
	  
      if(fh.getMap().at(i,j) != 0) {
	renderSprite.setPosition(i*32, j*32);
	renderSprite.setTexture(fh.getBlock(fh.getMap().at(i,j)));
	off_screen.draw(renderSprite);
      }
    }
  }
  off_screen.display();
    
  sf::Sprite off_sprite(off_screen.getTexture());
  Matrix mat{};
    
    
  /*
    sf::Music backMusic;
    backMusic.setPosition(0,0,0);
    backMusic.setVolume(30);
    backMusic.setLoop(true);
    backMusic.setPitch(0);

    backMusic.play();
  */
  Camera view{play1, 1024,800};

  //if(!backMusic.openFromFile("Data/Sounds/SummerLight.mp3"))
  // cerr << "Could not open sound file" << endl;
    
  Monster mon1{10, 320, 10, 10}; 
  while (window.isOpen()) {
    sf::Time deltaCounter{sf::microseconds(0)};
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
	window.close();
    }
      
    do {
      timer.restart();
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
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
	//play1.fire();
      }
	
      //Player-update
      play1.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000);
      //Monster-update
      mon1.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000, play1);
      //Object-update
      
      //Camera-update
      view.update(play1);
      //Render
      
        
      deltaTime = timer.getElapsedTime();
      //cout << deltaCounter.asMilliseconds() << endl;
      deltaCounter = deltaCounter + deltaTime;
    } while(deltaCounter < sf::milliseconds(15));

    window.clear();
    window.setView(view.getView());
    window.draw(off_sprite);
    renderSprite.setPosition(mon1.getX(), mon1.getY());
    renderSprite.setTexture(fh.getBlock(1));
    window.draw(renderSprite);
    playerSprite.setPosition(play1.getX(), play1.getY());
    playerSprite.setTexture(fh.getPlayer(0));

    window.draw(playerSprite);
      
    window.display();


      
  }

  return 0;
}
