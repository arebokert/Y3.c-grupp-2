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
#include "Objects/Bullet.h"
#include "Graphics/Camera.h"

using namespace std;

int main()
{
  bool multiplayer;
  string input = "";
  string play1Name = "";
  string play2Name = "";
  vector<Bullet*> bullets;
  vector<Monster*> monsters;
  
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
	
  do{
	cout << "Enter the name of player 1 below: " << endl;
	getline(cin, play1Name);
  } while (play1Name.empty());
  
  if(multiplayer) {
	do{
	   cout << "Enter the name of player 2 below (can not be the same as player 1!): " << endl;
	   getline(cin, play2Name);
	} while (play2Name.empty() || play2Name.compare(play1Name) == 0);
  }
	
  sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
  Player play1{10, 320, 10, 10};
  play1.pickUpWeapon(new Weapon{10,10,0,200,10,1000});
  Player play2{10, 320, 10, 10};
  play2.pickUpWeapon(new Weapon{10,10,0,200,10,1000});
  Monster* mon1 = new Monster{10, 320, 10, 10}; 
  monsters.push_back(mon1);
  
  FileHandler fh{"Fieldtest1"};

  sf::Clock timer{};
  sf::Time deltaTime{sf::milliseconds(2)};
  
  //Read font
  //-----------------------------------------
  sf::Font font;
  font.loadFromFile("./font.ttf");
  //-----------------------------------------
  
  //Set player name textures
  //-----------------------------------------
  sf::Text playerNameOne(play1Name, font);
  sf::Text playerNameTwo(play2Name, font);
  playerNameOne.setCharacterSize(20);
  playerNameOne.setStyle(sf::Text::Bold);
  playerNameOne.setColor(sf::Color::Red); 
  if(multiplayer){
	  playerNameTwo.setCharacterSize(20);
	  playerNameTwo.setStyle(sf::Text::Bold);
	  playerNameTwo.setColor(sf::Color::Green); 
  }
  //-----------------------------------------
  
  //Renders a hp bar over players
  //-----------------------------------------
  std::string hpP1{play1.getHpString()};
  std::string hpP2{play2.getHpString()};
  sf::Text hpTextP1(hpP1, font);
  sf::Text hpTextP2(hpP2, font);
  hpTextP1.setCharacterSize(20);
  hpTextP1.setStyle(sf::Text::Bold);
  hpTextP1.setColor(sf::Color::Red); 
  hpTextP2.setCharacterSize(20);
  hpTextP2.setStyle(sf::Text::Bold);
  hpTextP2.setColor(sf::Color::Green); 
  //-----------------------------------------

  //Creating off_screen texture for map
  //-----------------------------------------
  sf::Sprite renderSprite;
  sf::RenderTexture off_screen;
  if(!off_screen.create(256*32, 256*32))
    std::cerr << "Failed to load off_screen texture" << std::endl;

  for(int i{0}; i < 256; i++) {
    for(int j{0}; j < 256; j++) {
	 
      if(fh.getMap().at(i,j) > 0) {
	renderSprite.setPosition(i*32, j*32);
	renderSprite.setTexture(fh.getBlock(fh.getMap().at(i,j)));
	off_screen.draw(renderSprite);
      } else if(fh.getMap().at(i,j) == -1){
		  play1.setRelPosX(i*32);
		  play1.setRelPosY(j*32);
		  mon1->setRelPosX(i*32);
		  mon1->setRelPosY(j*32);
	  } else if(fh.getMap().at(i,j) == -2){
		  play2.setRelPosX(i*32);
		  play2.setRelPosY(j*32);
	  }
    }
  }
  off_screen.display();
    
  sf::Sprite off_sprite(off_screen.getTexture());
  //-----------------------------------------



  //Start background music
  fh.getMusic().play();

  Camera view{play1, 1024,800};
  
  static int frame = 0;

  
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
		++frame;
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
		if(play1.fire(play1.getLastDirection(), frame)){
			
			int offsetX;
			
			if(play1.getLastDirection() == -1)
				offsetX = -16;
			else
				offsetX = 25;
			
			Bullet* b = new Bullet( play1.getX() + offsetX, play1.getY() + 25, 
									play1.getLastDirection(), 
									play1.getActiveWeapon().getSpeed(), 
									play1.getActiveWeapon().getDamage());
			bullets.push_back(b);
			b->initBullet(frame);
		}
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
		if(play2.fire(play2.getLastDirection(), frame)){
			int offsetX;
			
			if(play2.getLastDirection() == -1)
				offsetX = -16;
			else
				offsetX = 25;
			
			Bullet* b = new Bullet( play2.getX() + offsetX, play2.getY() + 25, 
									play2.getLastDirection(), 
									play2.getActiveWeapon().getSpeed(), 
									play2.getActiveWeapon().getDamage());
			bullets.push_back(b);
			b->initBullet(frame);
		}
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
      play1.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000, frame);
      
      if(multiplayer) {
		play2.update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000, frame);
	  }
      //Monster-update
       mon1->update(fh.getMap(), static_cast<double>(deltaTime.asMicroseconds())/1000000, play1);
       if(multiplayer)
      {
		 mon1->update(fh.getMap(), 0, play2); 
	  }
	  
	  
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
    
    if (!bullets.empty()) {

		for (int i = 0; i < bullets.size(); ++i)
		{
			if (!bullets[i]->drawBullet(fh.getMap(), frame)) 
			{		
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
			
			else if(!monsters.empty()){
				for(int j = 0; j < monsters.size(); ++j){
					if(monsters[j]->isHit(bullets[i]->getX(), bullets[i]->getY())){
						if(monsters[j]->inflictDamage(bullets[i]->getDamage())){
							delete monsters[j];
							monsters.erase(monsters.begin() + j);
								
							delete bullets[i];
							bullets.erase(bullets.begin() + i);
							break;
						}
						break;
					}
					else{
						sf::Sprite bulletSprite;
						bulletSprite.setPosition(bullets[i]->getX(), bullets[i]->getY());
						bulletSprite.setTexture(fh.getBullet(bullets[i]->getTexID()));
						window.draw(bulletSprite);
					}
				}   
			}
			else{
				sf::Sprite bulletSprite;
				bulletSprite.setPosition(bullets[i]->getX(), bullets[i]->getY());
				bulletSprite.setTexture(fh.getBullet(bullets[i]->getTexID()));
				window.draw(bulletSprite);
			}
		}
	}
	
    
    sf::Sprite monsterSprite;
    monsterSprite.setPosition(mon1->getX(), mon1->getY());
    monsterSprite.setTexture(fh.getMonster(mon1->getTexId()));
    window.draw(monsterSprite);

    sf::Sprite playerSprite;
    playerSprite.setPosition(play1.getX(), play1.getY());
    playerSprite.setTexture(fh.getPlayer(play1.getTexId()));
    window.draw(playerSprite);
    
    sf::Sprite weaponSpriteP1;
    weaponSpriteP1.setPosition(play1.getActiveWeapon().getX(), play1.getActiveWeapon().getY());
    weaponSpriteP1.setTexture(fh.getWeapon(play1.getActiveWeapon().getTexDirected(play1.getLastDirection())));
    window.draw(weaponSpriteP1);
    
    sf::Sprite playerSprite2;
    playerSprite2.setPosition(play2.getX(), play2.getY());
    playerSprite2.setTexture(fh.getPlayer(play2.getTexId()));
    
    sf::Sprite weaponSpriteP2;
    weaponSpriteP2.setPosition(play2.getActiveWeapon().getX(), play2.getActiveWeapon().getY());
    weaponSpriteP2.setTexture(fh.getWeapon(play2.getActiveWeapon().getTexDirected(play2.getLastDirection())));
    
    if(multiplayer) {
		window.draw(playerSprite2);
		window.draw(weaponSpriteP2);
	}

    
    //Draws the playernames on the screen
	
	playerNameOne.setPosition(play1.getX(), play1.getY()-60);
	hpTextP1.setPosition(play1.getX(), play1.getY()-30);
	hpTextP1.setString(play1.getHpString());
    window.draw(playerNameOne);
    window.draw(hpTextP1);
    
	
	if(multiplayer) {
		playerNameTwo.setPosition(play2.getX(), play2.getY()-60);
		hpTextP2.setPosition(play2.getX(), play2.getY()-30);
		hpTextP2.setString(play2.getHpString());
		window.draw(playerNameTwo);
		window.draw(hpTextP2);
	}
	
    //Display everything
    window.display(); 
  }
  return 0;
}
