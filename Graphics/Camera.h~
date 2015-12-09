#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "../Objects/Player.h"

class Camera {
public:
	Camera() = default;
	~Camera() = default;
	Camera(Player& a, const int b, const int c) : 
		player(a), width(b), height(c) {};
	sf::View& getView() {return view;};
	void update(Player&);
private:
	Player player;
	int width{0};
	int height{0};
	sf::View view{};
	bool isNearBorder(int,int) {};
};


#endif
