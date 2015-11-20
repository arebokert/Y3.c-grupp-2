#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

class Object{
 public:
  ~Object() = default;
  Object(int, int);

  sf::Texture getText();
  virtual void update() const = 0;
  int getX();
  int getY();
  
 protected:
  Object() = default;

  int posX:
  int posY;
 
 private:
}
#endif
