#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
#include "Player.h"
#include "../Tools/Matrix.h"

class Monster : public Character {
public:
	Monster(int h, int s, int x, int y) : Character(h, s, x, y) {
		relPosX = static_cast<double>(x);
		relPosY = static_cast<double>(y);
	};
	void update(Matrix&, double, Player&);
	
private:
	void attack(Player&);
	bool goLeft{true};
	int damage;
};

#endif
