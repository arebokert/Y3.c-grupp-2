#include "Weapon.h"
#include "Objects.h"
#include "Bullet.h"
#include <vector>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

using namespace std;

void Weapon::fire(int rel_x, int rel_y, int direction) const
{ 
  Bullet b{rel_x, rel_y, texID, speed, damage};
  //bullets.push_back(b);
  b.fire(rel_x, rel_y, direction);
}

void Weapon::setEquipped()
{
  equipped = true;
}

void Weapon::update() const
{
}

void Weapon::update(int rel_x, int rel_y, int direction)
{
  setX(rel_x);
  setY(rel_y+31);

  //for(vector<Weapon>::iterator it = bullets_.begin(); it != bullets_.end(); it++)
  //{
  //*it->update();
  //}
}
