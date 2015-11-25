#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

class Object{
 public:
  ~Object() = default;
 Object(int x, int y, int texID) : posX(x), posY(y), texID(texID){};

  int getTexID();
  virtual void update() const = 0;
  int getX();
  int getY();
  
 protected:
  Object() = default;
  int texID;
  int posX;
  int posY;
 
 private:
}
#endif
