#ifndef WEAPON_H
#define WEAPON_H
#include "Objects.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>



class Weapon : public Objects
{
 public:
 Weapon(int x, int y, int texID, int w_speed, int w_damage) : Objects(x, y, texID), speed{w_speed}, damage{w_damage}{}
  ~Weapon() = default;
 Weapon& operator=(const Weapon&) = delete; 
 void fire(int, int, int) const override;
 void update() const;

 protected:
 Weapon(const Weapon&); 

 private:
 Weapon() = default;

 int speed;
 int damage; 

 sf::Time cooldown;
 sf::Clock timer;
};

#endif
