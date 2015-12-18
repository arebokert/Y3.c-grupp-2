#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Tools/Matrix.h"
#include <string>

class Character {
//using string = std::string;
public:
	Character(int h, int s, int x, int y) : hp(h), speed(s), posX(x), posY(y) {};
	Character() = default;
	void updateHpString();
	int getTexId() {return texId;};
	int getHp() const {return hp;};
	int getX() const {return posX;};
	int getY() const {return posY;};
	std::string getHpString() const {return hpString;};
	
	
	int setHp(int h){hp = h;};
	int setX(int x){posX = x;};
	int setY(int y){posY = y;};
	void setHpString(std::string hs){hpString = hs;};
	int setTexId(int txId){texId = txId;};
	//void update(Matrix&) {};
protected:
	std::string hpString;
	int hp{0};
	int speed{0};
	int posX{0};
	int posY{0};
	int texId{0};
	double relPosX{0};
	double relPosY{0};
	float ySpeed{0};
	float xSpeed{0};
};

#endif
