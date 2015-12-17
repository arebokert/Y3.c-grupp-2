#ifndef WEAPON_H
#define WEAPON_H
#include "Objects.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>



class Weapon : public Objects
{
 public:
 Weapon(int x, int y, int texID, int w_speed, int w_damage, int cooldown) : 
 Objects(x, y, texID), speed{w_speed}, damage{w_damage}, cd{cooldown}{}
 Weapon(const Weapon&);
 ~Weapon() = default;
 Weapon& operator=(const Weapon&) = delete; 
 void fire(int, int, int, const int);
 void update() const;
 void update(int, int, int, const int);
 void setEquipped();
 int getTexDirected(int direction);
 void getBullets();

 private:
 Weapon() = default;

 //bool lockout = false;
 int cd;
 int speed;
 int damage;
 int lockout;
 bool equipped; 
 std::vector<Bullet> bullets;

 sf::Time cooldown;
 sf::Clock timer;
};

#endif
