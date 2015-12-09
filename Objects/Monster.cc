#include "Monster.h"
#include <math.h>

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
  

  //Collision-check on x-axis
  if(mat.at(floor(posX/32)+1, floor(posY/32)) != 0 && xSpeed > 0 ||
     mat.at(floor(posX/32), floor(posY/32)) != 0 && xSpeed < 0)
    xSpeed = 0;
  relPosX += xSpeed*delta;
  //Set new positions

  if(posY != static_cast<int>(relPosY))
    posY = static_cast<int>(relPosY);

  if(posX != static_cast<int>(relPosX))
    posX = static_cast<int>(relPosX);
    
 //Checks the distance between the monster and player. 
 //If the distance in less than 20px (both X and Y value), the monster attacks the player
  if(((getX()-play.getX()) >= 20 && (getY()-play.getY()) >= 20)
	||((play.getX()-getX()) <= 20 && (play.getY()-getY()) <= 20))
	{
		this->attack(play);
	}
  }
  
  void Monster::attack(Player& play)
  {
	  play.setHp(play.getHp()-1);
  }
  
