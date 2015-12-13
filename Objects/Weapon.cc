#include "Weapon.h"
#include "Objects.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

void Weapon::fire(int rel_x, int rel_y, int direction) const
{
  //
  //int trajectory = weapon_relative_pos()
  Bullet b{rel_x, rel_y, texID, speed, damage};
  b.fire(rel_x, rel_y, direction);
}

void Weapon::setEquipped()
{
  equipped = true;
}

void Weapon::update() const
{
}

void Weapon::update(int rel_x, int rel_y)
{
}
