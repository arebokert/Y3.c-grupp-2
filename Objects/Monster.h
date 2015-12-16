#ifndef MONSTER_H
#define MONSTER_H
#include <SFML/System.hpp>
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
	sf::Clock monsterAnimationTimer{};
	void updateTexture();
	int counterMonster;
	sf::Clock clock;
	void attack(Player&);
	bool goRight{true};
	int damage;
};

#endif
