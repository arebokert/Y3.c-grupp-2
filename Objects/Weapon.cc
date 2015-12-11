#include "Weapon.h"
#include "Objects.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

void Weapon::fire(int rel_x, int rel_y) const
{
  //
  //int trajectory = weapon_relative_pos()
  Bullet b{speed, damage};
  b.fire(rel_x, rel_y);
}

void Weapon::update() const
{
}
