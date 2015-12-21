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
	~Monster() = default;
	void update(Matrix&, double, Player&);
	bool isHit(int, int);
	bool inflictDamage(int);
	
private:
	sf::Clock monsterAnimationTimer{};
	void updateTexture();
	int counterMonster{0};
	sf::Clock clock;
	void attack(Player&);
	bool goRight{true};
	int damage;
	int width{42};
	int height{62};
};

#endif
