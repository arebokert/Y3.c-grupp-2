#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Object.h"

class Bullet : Object
{
 public:
 Bullet(int nSpeed, int nDamage) : speed{nSpeed}, damage{nDamage};
 void fire(int, int) const override;
 void update(Matrix&, playerY) const override;

 Bullet& operator=(const Bullet&) = delete; 

 protected:
 Bullet(const& Bullet);
 
 private:
 int speed;
 int damage;
}

#endif
