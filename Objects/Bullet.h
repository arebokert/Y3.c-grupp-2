#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Object.h"

class Bullet : Object
{
 public:
 Bullet() : public Object();
 operator=(const Bullet&) = delete; 

 protected:
 Bullet(const& Bullet);
 private:
}

#endif
