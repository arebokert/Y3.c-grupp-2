#include "Monster.h"

using namespace std;


void Monster::update(Matrix& mat, double delta,Player& play) {
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
	
    //Collision-check on x-axis
  if(mat.at(floor(posX/32)+1, floor(posY/32)) != 0 && xSpeed > 0 ||
     mat.at(floor(posX/32), floor(posY/32)) != 0 && xSpeed < 0)
    xSpeed = 0;
  relPosX += xSpeed*delta;
  //Set new positions

  if(posY != static_cast<int>(relPosY))
	{
    posY = static_cast<int>(relPosY);
	}
  
  if(posX != static_cast<int>(relPosX))
	{
    posX = static_cast<int>(relPosX);
	} 
 //Checks the distance between the monster and player. 
 //If the distance in less than 20px (both X and Y value), the monster attacks the player
  if((self.getX()-play.getX()=<20)&&(self.getY()-play.getY()=<20)
	{
		attack();
	}
  }
  
  void Monster::attack(Player& play)
  {
	  play.setHp(play.getHp()-1);
  }
  
