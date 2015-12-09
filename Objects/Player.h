#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "../Tools/Matrix.h"

class Player : public Character {
public:
	Player(int h, int s, int x, int y) : Character(h, s, x, y) {
		relPosX = static_cast<double>(x);
		relPosY = static_cast<double>(y);
	};
	void moveLeft();
	void moveRight();
	void jump();
	void update(Matrix&, double);
private:
    bool canJump{true};
	
	
};


#endif
