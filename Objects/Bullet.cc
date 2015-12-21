#include "Bullet.h"
#include "../Tools/Matrix.h"
#include "Objects.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void Bullet::initBullet(const int frame)
{
	setFrameStart(frame);
}

bool Bullet::drawBullet(Matrix& mat, const int frame)
{
	// Vart är bullet nu?
	int deltaFrame = frame - frameStart;
	
	int blocks = floor(deltaFrame / speed);
	
	setX(getX() + (deltaFrame / speed) * texID);
	
	blocks *= texID;
	
	// Collision-detection
	if (mat.at(floor(static_cast<double>(getX())/32), floor(static_cast<double>(getY())/32)) != 0)
	{
		return false;
	}
	
	return true;
}

int Bullet::getDamage(){
	return damage;
}

void Bullet::setFrameStart(const int frame)
{
	frameStart = frame;
}

