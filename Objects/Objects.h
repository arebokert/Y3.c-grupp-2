#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

class Objects{
 public:
  ~Objects() = default;
 Objects(int x, int y, int texID) : posX(x), posY(y), texID(texID){};

  virtual void update() const = 0;
  int getTexID() const {return texID;};
  int getX() const {return posX;};
  int getY() const {return posY;};
  int setX(int x){posX = x;};
  int setY(int y){posY = y;};
  //virtual void fire(int, int, int, const int) = 0;  

 protected:
  Objects() = default;
  int texID{0};
  int posX{0};
  int posY{0};
 
 private:
};
#endif
