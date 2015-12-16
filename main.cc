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
  Player play1{10, 320, 10, 10};
  FileHandler fh{"Fieldtest1"};
  int x{0};
  int y{0};
    
  sf::Sprite renderSprite;
  int direction{0};
  //Variable lastDirection keeps track of the last movements of the player
  //i.e movement before player stops.
  int lastDirection{0};
  sf::Sprite playerSprite;
  sf::Clock timer{};
  sf::Clock animationTimer{};
  int counter{0};
  sf::Time deltaTime{sf::milliseconds(2)};
  //Set initial texture to playerSprite
  playerSprite.setTexture(fh.getPlayer(0));
  sf::RenderTexture off_screen;
  
  //Renders a hp bar over players
  std::string hp{play1.getHpString()};
  sf::Font font;
  font.loadFromFile("./font.ttf");
  sf::Text text(hp, font);
  text.setCharacterSize(20);
  text.setStyle(sf::Text::Bold);
  text.setColor(sf::Color::Red); 
    
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
	direction = 1;
	lastDirection = 1;
	play1.moveRight();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	direction = -1;
	lastDirection = -1;
	play1.moveLeft();
      }
      else {
        direction = 0;
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
      {
	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
      {
	fh.getJumpSound().play();
	play1.jump();
	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
	play1.fire(lastDirection);
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
    //cout << play1.getX() << endl<< mon1.getX() << endl;
    window.clear();
    window.setView(view.getView());
    window.draw(off_sprite);
    renderSprite.setPosition(mon1.getX(), mon1.getY());
    renderSprite.setTexture(fh.getBlock(1));
    window.draw(renderSprite);
    playerSprite.setPosition(play1.getX(), play1.getY());
    
    //This if-statement changes the sprite when the player moves
    if(direction != 0){
      int elapsedTime{animationTimer.getElapsedTime().asMilliseconds()};
      if(elapsedTime >= 100 && play1.getCanJump())
      {
		if(counter >= 3)
        {
			counter = 0;
        }
        if(direction == 1)
        {
			playerSprite.setTexture(fh.getPlayer(counter));
        } 
        else
        {
			playerSprite.setTexture(fh.getPlayer(counter+3));
        }
        counter++;
        animationTimer.restart();
      }
      else if(!play1.getCanJump()){
		if(lastDirection == 1){
		  playerSprite.setTexture(fh.getPlayer(6));
		}
		else {
		  playerSprite.setTexture(fh.getPlayer(7));
		}
		counter = 0;
		animationTimer.restart();
	  }
    }
    //these two else-ifs checks the last direction of the players movement
    //to properly set texture when player stop moving
    else if (lastDirection == -1 && play1.getCanJump())
    {
		playerSprite.setTexture(fh.getPlayer(3));
	}
	else if (lastDirection == 1 && play1.getCanJump())
	{
		playerSprite.setTexture(fh.getPlayer(0));
	}
	else if (lastDirection == -1 && !play1.getCanJump())
	{
		playerSprite.setTexture(fh.getPlayer(7));
	}
	else if (lastDirection == 1 && !play1.getCanJump())
	{
		playerSprite.setTexture(fh.getPlayer(6));
	}
    window.draw(playerSprite);
	text.setPosition(play1.getX(), play1.getY()-30);
	// Draw it
	window.draw(text);
	//updates hp bar
    hp=play1.getHpString();
    text.setString(hp);
    window.display(); 
  }
  return 0;
}
