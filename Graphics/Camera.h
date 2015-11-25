#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
public:
	Camera() = default;
	~Camera() = default;
	Camera(const Player& a, const int b, const int c, sf::View& d) : 
		player(a), width(b), height(c), view(d) {};
	sf::View& getView() {return view;};
private:
	Player player{};
	int width{0};
	int height{0};
	sf::View view{};
	void update();
	bool isNearBorder(int,int);
};


#endif
