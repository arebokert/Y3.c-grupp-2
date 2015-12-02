#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <Clock.hpp>
#include <Time.hpp>

class Weapon : Objects
{
 public:
 Weapon(int x, int y, int texID, int w_speed, int w_damage) : Objects(x, y, texID), speed{w_speed}, damage{w_damage}{}
  ~Weapon() = default;
 operator=(const Weapon&) = delete; 

 protected:
 Weapon(const Weapon&); 

 private:
 Weapon() = default;

 //Eller hur var det tänkt?
 int speed;
 int damage; 

 sf::Time cooldown;
 sf::Clock timer;
}

#endif
