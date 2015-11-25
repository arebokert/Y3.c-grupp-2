#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>

class Weapon : Objects
{
 public:
 Weapon(int x, int y, int texID) : Objects(x, y, texID);
  ~Weapon() = default;
 
 protected:

 private:

}
