#include "Bullet.h"
#include "../Tools/Matrix.h"
#include "Objects.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void Bullet::initBullet(const int frame)
{
	setFrameStart(frame);
	cout << getX() << " " << getY() << " " << texID;
}

bool Bullet::drawBullet(Matrix& mat, const int frame)
{
	// Vart är bullet nu?
	int deltaFrame = frame - frameStart;
	
	int blocks = floor(deltaFrame / speed);
	
	setX(getX() + (deltaFrame / speed) * texID);
	
	blocks *= texID;
	
	// Collision-detection
	if (mat.at( (getX() / 32) + blocks, getY() / 32) != 0 || getX() < -500)
	{
		return false;
	}
	
	
	return true;
}

void Bullet::setFrameStart(const int frame)
{
	frameStart = frame;
}

