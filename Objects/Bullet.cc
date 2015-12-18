#include "Bullet.h"
#include "../Tools/Matrix.h"
#include "Objects.h"
#include <iostream>
//#include <SMFL/Graphics.hpp>

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
	
	blocks *= texID;
	
	// Collision-detection
	if (mat.at( (getX() / 32) + blocks, getY() / 32) != 0)
	{
		cout << "Bullet destroyed at " << (getX() / 32) + blocks;
		return false;
	}
	
	cout <<  blocks << endl;
	return true;
	// Kolla om bullet-position är i en vägg
	/* if(mat.at(floor((posX+width)/32), floor(posY/32)) != 0 && xSpeed > 0 ||
		mat.at(floor((posX+width)/32), floor((posY+height-1)/32)) != 0 && xSpeed > 0 ||
		mat.at(floor(posX/32), floor(posY/32)) != 0 && xSpeed < 0 ||
		mat.at(floor(posX/32), floor((posY+height-1)/32)) != 0 && xSpeed < 0)*/
}

void Bullet::setFrameStart(const int frame)
{
	frameStart = frame;
}

