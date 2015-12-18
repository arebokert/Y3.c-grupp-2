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
  Bullet* b = new Bullet{rel_x, rel_y, direction, speed, damage};
  bullets.push_back(b);
  b->initBullet(frame);
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

void Weapon::update(Matrix& mat, const int frame) const
{
	return;
}

void Weapon::update(Matrix& mat, int rel_x, int rel_y, int direction, const int frame)
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
	
	if (!bullets.empty()) {
		/*for(auto it = bullets.begin(); it != bullets.end(); it++) {
			if(!it->drawBullet(mat, frame)){
				it = bullets.erase(it);
			}
		}*/
		
		for (int i = 0; i < bullets.size(); ++i)
		{
			if (!bullets[i]->drawBullet(mat, frame)) 
			{		
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}
	}
}
