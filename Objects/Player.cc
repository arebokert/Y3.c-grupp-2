#include "Player.h"
#include <math.h>
#include <iostream>
using namespace std;

void Player::moveLeft() {
  xSpeed = -speed;
}

void Player::moveRight() {
  xSpeed = speed;
}

void Player::jump() {
  if(canJump){
	ySpeed = -240;
  }
}

void Player::update(Matrix& mat, double delta) {
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
  
  if(mat.at(floor((posX+1)/32), floor((posY+height)/32)) == 0 &&
     mat.at(floor((posX+width-1)/32), floor((posY+height)/32)) == 0) {
    ySpeed += 600*delta;
    canJump = false;
  }
  else {
	canJump = true;
    ySpeed = 0;
  }
  

  //Collision-check on x-axis
  if(mat.at(floor((posX+width)/32), floor(posY/32)) != 0 && xSpeed > 0 ||
     mat.at(floor((posX+width)/32), floor((posY+height-1)/32)) != 0 && xSpeed > 0 ||
     mat.at(floor(posX/32), floor(posY/32)) != 0 && xSpeed < 0 ||
     mat.at(floor(posX/32), floor((posY+height-1)/32)) != 0 && xSpeed < 0)
    xSpeed = 0;
  relPosX += xSpeed*delta;
  //Set new positions

  if(posY != static_cast<int>(relPosY))
    posY = static_cast<int>(relPosY);

  if(posX != static_cast<int>(relPosX))
    posX = static_cast<int>(relPosX);

  //Reset x-axis speed from player input
  xSpeed = 0;
  
  


  
}
