#include "Player.h"
#include "Weapon.h"
#include <math.h>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

void Player::moveLeft() {
  xSpeed = -speed;
  direction = -1;
  lastDirection = -1;
}

void Player::moveRight() {
  xSpeed = speed;
  direction = 1;
  lastDirection = 1;
}

void Player::jump() {
  if(canJump){
	ySpeed = -240;
  }
}

/**
 * Gets the availability of the jump action.
 * @return Whether or not the player can jump.
 */
bool Player::getCanJump(){
  return canJump;
}

bool Player::pickUpWeapon(Weapon* new_wep){
  weapons.push_back(new_wep);
  return true;
}

void Player::switchWeapon(int pressed){
  if(pressed > weapons.size()){
    return;
  }
  activeWeapon = weapons.at(pressed);
}

void Player::fire(int direction){
  if(activeWeapon != nullptr){
    activeWeapon->fire(static_cast<int>(relPosX), static_cast<int>(relPosY), direction);
  }
}

//Function that updates the hp bar over the player
void Character::updateHpString(){
	std::string tempHp{""};
	for(int i{0};i<=getHp();i++)
	{
		tempHp.append("*");
	}
	setHpString(tempHp);
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
  
  //activeWeapon->update(posX,posY);
  
  //calls function that updates the hp bar over the player
  updateHpString();
  updateTexture();
  //activeWeapon->update(posX, posY, direction);
}
void Player::updateTexture()
{
	//int counter{0};
	cout << direction << endl;
	if(direction != 0){
      int elapsedTime{animationTimer.getElapsedTime().asMilliseconds()};
      if(elapsedTime >= 100 && canJump)
      {
		if(counter > 2)
        {
			counter = 0;
        }
        if(direction == 1)
        {
			setTexId(counter);
        } 
        else
        {
			setTexId(counter+3);
        }
        counter++;
        animationTimer.restart();
      }
      else if(!canJump){
		if(lastDirection == 1){
		  setTexId(6);
		}
		else {
		  setTexId(7);
		}
		counter = 0;
		animationTimer.restart();
	  }
    }
    //these else-ifs checks the last direction of the players movement
    //to properly set texture when player stop moving
    else if (lastDirection == -1 && canJump)
    {
		setTexId(3);
	}
	else if (lastDirection == 1 && canJump)
	{
		setTexId(0);
	}
	else if (lastDirection == -1 && !canJump)
	{
		setTexId(7);
	}
	else if (lastDirection == 1 && !canJump)
	{
		setTexId(6);
		
	}
	direction = 0;
}
