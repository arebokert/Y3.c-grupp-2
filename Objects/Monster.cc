#include "Monster.h"
#include <math.h>
#include <iostream>

using namespace std;


void Monster::update(Matrix& mat, double delta, Player& play) {
  //Speed will have to be dependent on delta time
  //Fix later when time-step has been added
  
  //y = new Y position
  //y0 = current Y position
  //g = pixels per second, g = 9.82*32 (32pix = 1m)
  //t = delta time
  //y = y0 - g * t^2 / 2
  //Apply gravity
  

  //Collision-check beneath
  //cout << "Delta time: " << delta << endl;
  
  
  
  if(ySpeed*delta < 6)
    relPosY += ySpeed*delta;
  else
    relPosY += 6;
  
  if(mat.at(floor(posX/32), floor(posY/32)+1) == 0) {
    ySpeed += 600*delta;
  }
  else {
    ySpeed = 0;
  }

  if(goRight)
    xSpeed = 300;
  else
    xSpeed = -300;
  

  //Collision-check on x-axis
  if(mat.at(floor(posX/32)+1, floor(posY/32)) != 0 && xSpeed > 0 ||
     mat.at(floor(posX/32), floor(posY/32)) != 0 && xSpeed < 0) {
    xSpeed = 0;
    goRight = !goRight;
  }
  relPosX += xSpeed*delta;
  //Set new positions

  if(posY != static_cast<int>(relPosY))
    posY = static_cast<int>(relPosY);

  if(posX != static_cast<int>(relPosX))
    posX = static_cast<int>(relPosX);
    
 //Checks the distance between the monster and player. 
 //If the distance in less than 40px (both X and Y value) and atleast 3 seconds
 //have passed since the last attack the monster attacks the player
	if(clock.getElapsedTime().asMilliseconds() >=3000)
	{
		if((std::abs(getX()-play.getX()) >=0 && std::abs(getX()-play.getX())<=40)|| 
		  (std::abs(play.getX()-getX()) <=0 && std::abs(play.getX()-getX())>=-40))
		{	
			this->attack(play);	
		}
	
		else if ((std::abs(getX()-play.getX()) >=0 && std::abs(getX()-play.getX())<=40)|| 
			(std::abs(play.getX()-getX()) <=0 && std::abs(play.getX()-getX())>=-40))
		{
			this->attack(play);
		}
	clock.restart();
  }
	updateTexture();
}
//Function that enables the Monster to attack the player
  void Monster::attack(Player& play)
  {	
	  cout << clock.getElapsedTime().asMilliseconds() << endl;
	  play.setHp(play.getHp()-1);
  }
  void Monster::updateTexture()
  {
	  
	  int elapsedTimeMonster{monsterAnimationTimer.getElapsedTime().asMilliseconds()};
      if(elapsedTimeMonster >= 100)
      {
		if(counterMonster > 2)
        {
			counterMonster = 0;
        }
        if(goRight == false)
        {
			counterMonster = counterMonster + 3;
        } 
       setTexId(counterMonster); 
       counterMonster++;
       monsterAnimationTimer.restart();   
      }
  }
  
