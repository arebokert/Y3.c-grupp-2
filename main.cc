#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include "Tools/Matrix.h"
#include "Filehandler/Filehandler.h"
#include "Objects/Player.h"
#include "Objects/Weapon.h"
#include "Objects/Monster.h"
#include "Graphics/Camera.h"

using namespace std;

int main()
{
  sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
  Player play1{10, 320, 10, 10};
  play1.pickUpWeapon(new Weapon{10,10,0,10,10});
  FileHandler fh{"Fieldtest1"};

  sf::Clock timer{};
  sf::Time deltaTime{sf::milliseconds(2)};
  

  //Set initial texture to playerSprite  SKALL TAS BORT
  playerSprite.setTexture(fh.getPlayer(0));
  weaponSprite.setTexture(fh.getWeapon(0));
  
  
  //Renders a hp bar over players
  //-----------------------------------------
  std::string hp{play1.getHpString()};
  sf::Font font;
  font.loadFromFile("./font.ttf");
  sf::Text text(hp, font);
  text.setCharacterSize(20);
  text.setStyle(sf::Text::Bold);
  text.setColor(sf::Color::Red); 
  //-----------------------------------------


  //Creating off_screen texture for map
  //-----------------------------------------
  sf::Sprite renderSprite;
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
  //-----------------------------------------



  //Start background music
  fh.getMusic().play();

  Camera view{play1, 1024,800};
  
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
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	play1.moveLeft();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	fh.getJumpSound().play();
	play1.jump();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
	play1.fire(play1.getLastDirection());
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
      deltaCounter = deltaCounter + deltaTime;

    } while(deltaCounter < sf::milliseconds(15));

    
    window.clear();
    window.setView(view.getView());
    window.draw(off_sprite);

    renderSprite.setPosition(mon1.getX(), mon1.getY());
    renderSprite.setTexture(fh.getBlock(1));
    window.draw(renderSprite);

    sf::Sprite playerSprite{};
    playerSprite.setPosition(play1.getX(), play1.getY());
    playerSprite.setTexture(fh.getPlayer(play1.getTexId()));
    window.draw(playerSprite);

    sf::Sprite weaponSprite{};
    weaponSprite.setPosition(play1.getActiveWeapon()->getX(), play1.getActiveWeapon()->getY());
    weaponSprite.setTexture(fh.getMonster(mon1.getTexId()));
    window.draw(weaponSprite);
    
    //HP bar
    text.setPosition(play1.getX(), play1.getY()-30);
    text.setString(play1.getHpString());
    window.draw(text);

    //Display everything
    window.display(); 
  }
  return 0;
}
