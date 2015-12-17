#include "Bullet.h"
#include "../Tools/Matrix.h"
#include "Objects.h"
//#include <SMFL/Graphics.hpp>

using namespace std;

void Bullet::drawBullet(int weapon_x, int weapon_y, int direction, const int frame)
{
	setX(weapon_x);
	setY(weapon_y);
	setFrameStart(frame);
}

void Bullet::update() const
{
	
}

void Bullet::setFrameStart(const int frame)
{
	frameStart = frame;
}

