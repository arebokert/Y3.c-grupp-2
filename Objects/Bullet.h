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
 void drawBullet(int, int, int, const int);
 void update() const override;

 Bullet& operator=(const Bullet&); 
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
