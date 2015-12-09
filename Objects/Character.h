#ifndef CHARACTER_H
#define CHARACTER_H


class Character {
public:
	Character(int h, int s, int x, int y) : hp(h), speed(s), posX(x), posY(y) {};
	Character() = default;
	int getTexId() {return texId;};
	int getHp() const {return hp;};
	int getX() const {return posX;};
	int getY() const {return posY;};
	
	int setHp(int h){hp = h;};
	int setX(int x){posX = x;};
	int setY(int y){posY = y;};
	int setTexId(int txId){texId = txId;};
	//void update(Matrix&) {};
protected:
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
