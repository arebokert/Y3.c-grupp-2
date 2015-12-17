#include "Weapon.h"
#include "Objects.h"
#include "Bullet.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

using namespace std;

void Weapon::fire(int rel_x, int rel_y, int direction, const int frame)
{ 
  if(frame < lockout ){
	return;
  }
  
  lockout = frame + cd;
  Bullet b{rel_x, rel_y, direction, speed, damage};
  bullets.push_back(b);
  b.drawBullet(rel_x, rel_y, direction, frame);
  cout << "Bam!" << endl;
}

void Weapon::setEquipped()
{
  equipped = true;
}

int Weapon::getTexDirected(int direction){
	if(direction == -1){
		return getTexID();
	} else if(direction == 1){
		return getTexID()+1;
	} else {
		return getTexID()+1;
	}
}

void Weapon::update() const
{
	if (!bullets.empty()) {
		for(auto it = bullets.begin(); it != bullets.end(); it++) {
			it->update();
		}
	}
}

void Weapon::update(int rel_x, int rel_y, int direction, const int frame)
{
	//Protection against frame overflowing, thus causing weapons to lock.
	if (frame == 0)
		{
			if ((std::numeric_limits<int>::max() - lockout) < cd)
			{
				int deltaFrame = std::numeric_limits<int>::max() - lockout;
				lockout = cd - deltaFrame;
			}
			else
			{
				lockout = 0;
			}
		}
	
	if(direction == 1)
	{
		setX(rel_x + 25);
	}
	else
	{
		setX(rel_x - 16);
	}

	setY(rel_y + 25);
	
	if(frame < cd) {
		lockout = true;
	}
}
