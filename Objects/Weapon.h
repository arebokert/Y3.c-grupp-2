#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>

class Weapon : Objects
{
 public:
 Weapon(int x, int y, int texID, int speed, int damage) : Objects(x, y, texID, speed, damage);
  ~Weapon() = default;
 
 protected:

 private:

}
