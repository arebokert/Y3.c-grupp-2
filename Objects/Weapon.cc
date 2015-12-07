#include "Weapon.h"
#include "Objects.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <Clock.hpp>
#include <Time.hpp>

Weapon::fire(int rel_x, int rel_y)
{
  //
  //int trajectory = weapon_relative_pos()
  Bullet b = new Bullet{speed, damage};
  b.fire(rel_x, rel_y);
}

void Weapon::update() const
{
}
