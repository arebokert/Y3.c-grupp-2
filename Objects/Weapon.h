#ifndef WEAPON_H
#define WEAPON_H
#include "Objects.h"
#include "Bullet.h"
#include "../Tools/Matrix.h"
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
 bool fire(int, int, int, const int);
 void update(Matrix&, const int) const override;
 void update(Matrix&, int, int, int, const int);
 void setEquipped();
 int getTexDirected(int direction);
 void getBullets();
 int getSpeed(){return speed;}
 int getDamage(){return damage;}

 private:
 Weapon() = default;

 //bool lockout = false;
 int cd;
 int speed;
 int damage;
 int lockout{0};
 bool equipped; 
 std::vector<Bullet*> bullets;

 sf::Time cooldown;
 sf::Clock timer;
};

#endif
