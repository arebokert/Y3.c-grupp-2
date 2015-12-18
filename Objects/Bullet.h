#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Objects.h"
#include "../Tools/Matrix.h"

class Bullet : public Objects
{
 public:
 Bullet(int x, int y, int texID, int w_speed, int w_damage) : Objects(x, y, texID), speed{w_speed}, damage{w_damage}{}
 ~Bullet() = default;
 void initBullet(const int);
 bool drawBullet(Matrix&, const int);
 void update(Matrix&, const int) const override{}
 int getDamage();
 Bullet& operator=(const Bullet&) = default; 
 Bullet(const Bullet&) = default;


 protected:
 //Bullet(const Bullet&);
 
 private:
 void setFrameStart(const int);
 
 int speed;
 int damage;
 int frameStart;
};

#endif
