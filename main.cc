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
  bool multiplayer;
  string input = "";
  string play1Name = "";
  string play2Name = "";
  
  do{
    cout << "Multiplayer mode? y/n" << endl;
    getline(cin, input);
    if(input == "y" || input == "Y") {
	  multiplayer = true;
    } 
    else if (input == "n" || input == "N") {
	  multiplayer =  false;
    }
  } while(input != "Y" && input != "y" && input != "n" && input != "N");
	
  cout << "Enter the name of player 1 below: " << endl;
  getline(cin, play1Name);
  
  while (play1Name.empty()){
		cout << "Enter a name, damn it:" << endl;
		getline(cin, play1Name);
  }  
  
  if(multiplayer) {
	cout << "Enter the name of player 2 below: " << endl;
	getline(cin, play2Name);
	
	while (play2Name.empty() || play2Name.compare(play1Name) == 0){
		cout << "Name is either empty or already taken! Try again, knucklehead: " << endl;
		getline(cin, play2Name);
	}  
  }
	
  sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
  Player play1{10, 320, 10, 10};
  play1.pickUpWeapon(new Weapon{10,10,0,10,10});
  Player play2{10, 320, 10, 10};
  play2.pickUpWeapon(new Weapon{10,10,0,10,10});
  
  FileHandler fh{"Fieldtest1"};

  sf::Clock timer{};
  sf::Time deltaTime{sf::milliseconds(2)};
  
  
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

  
  sf::Clock fpsTimer;
  while (window.isOpen()) {
    sf::Time deltaCounter{sf::microseconds(0)};
    sf::Event event;

    fpsTimer.restart();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
	window.close();
    }
    
    do {
      timer.restart();
      //Player 1-input
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	play1.moveRight();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	play1.moveLeft();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if(play1.getCanJump())
		  fh.getJumpSound().play();
		play1.jump();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
	//play1.fire(play1.getLastDirection());
      }
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
		play1.switchWeapon(0);  
	  }
	  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
		play1.switchWeapon(1);  
	  }
	  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
		play1.switchWeapon(2);  
	  }
      //Player 2-input
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && multiplayer) {
		play2.moveRight();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && multiplayer) {
		play2.moveLeft();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && multiplayer) {
		if(play2.getCanJump())
		  fh.getJumpSound().play();
		play2.jump();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && multiplayer) {
	//play2.fire(play1.getLastDirection());
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && multiplayer) {
		play2.switchWeapon(0);  
	  }
	  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && multiplayer) {
		play2.switchWeapon(1);  
	  }
	    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && multiplayer) {
		play2.switchWeapon(2);  
	  }

      //Player-update
      play1.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000);
      
      if(multiplayer) {
		play2.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000);
	  }
      //Monster-update
      mon1.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000, play1);
      //Object-update
      
      //Camera-update
      view.update(play1);
      //Render

        
      deltaTime = timer.getElapsedTime();
      deltaCounter = deltaCounter + deltaTime;

    } while(deltaCounter < sf::milliseconds(14));

    
    window.clear();
    window.setView(view.getView());
    window.draw(off_sprite);
    
    sf::Sprite monsterSprite;
    monsterSprite.setPosition(mon1.getX(), mon1.getY());
    monsterSprite.setTexture(fh.getMonster(mon1.getTexId()));
    window.draw(monsterSprite);

    sf::Sprite playerSprite;
    playerSprite.setPosition(play1.getX(), play1.getY());
    playerSprite.setTexture(fh.getPlayer(play1.getTexId()));
    window.draw(playerSprite);
    
    sf::Sprite playerSprite2;
    playerSprite2.setPosition(play2.getX(), play2.getY());
    playerSprite2.setTexture(fh.getPlayer(play2.getTexId()));
    
    if(multiplayer) {
		window.draw(playerSprite2);
	}

    sf::Sprite weaponSprite{};
    weaponSprite.setPosition(play1.getActiveWeapon().getX(), play1.getActiveWeapon().getY());
    weaponSprite.setTexture(fh.getWeapon(play1.getActiveWeapon().getTexDirected(play1.getLastDirection())));
    window.draw(weaponSprite);
    
    //Draws the playernames on the screen
	sf::Text playerNameOne(play1Name, font);
	playerNameOne.setCharacterSize(20);
	playerNameOne.setStyle(sf::Text::Bold);
	playerNameOne.setColor(sf::Color::Red); 
	
	playerNameOne.setPosition(play1.getX(), play1.getY()-60);
    window.draw(playerNameOne);
	
	if(multiplayer) {
		sf::Text playerNameTwo(play2Name, font);
		playerNameTwo.setCharacterSize(20);
		playerNameTwo.setStyle(sf::Text::Bold);
		playerNameTwo.setColor(sf::Color::Green); 
		
		playerNameTwo.setPosition(play2.getX(), play2.getY()-60);
		window.draw(playerNameTwo);
	}
	
    //HP bar
    text.setPosition(play1.getX(), play1.getY()-30);
    text.setString(to_string(fpsTimer.getElapsedTime().asMilliseconds()));
    window.draw(text);
	
    //Display everything
    window.display(); 
  }
  return 0;
}
