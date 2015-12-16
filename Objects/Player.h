#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "Weapon.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Tools/Matrix.h"

class Player : public Character {
public:
	Player(int h, int s, int x, int y) : Character(h, s, x, y) {
		relPosX = static_cast<double>(x);
		relPosY = static_cast<double>(y);
	};
	
	int getLastDirection(){return lastDirection;};
	int getDirection(){return direction;};
	int setY(int y){posY = y;};
	void moveLeft();
	void moveRight();
	void jump();
	void fire(int);
	void update(Matrix&, double);
	bool pickUpWeapon(Weapon*);
	void switchWeapon(int);
	bool getCanJump();
private:
	int direction{0};
	int lastDirection{0};
	void updateTexture();
    bool canJump{true};
	float ySpeed{0};
	float xSpeed{0};
	int width{45};
	int height{62};
	std::vector<Weapon*> weapons;
	Weapon* activeWeapon;
};


#endif
