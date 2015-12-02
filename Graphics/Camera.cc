#include "Camera.h"
#include <iostream>
#include <math.h>
void Camera::update(Player& p) {
  
  //Check where player is in the Array-coordinate system
  // x = static_cast<int>(Math.floor(player.getX()/32));
  // y = static_cast<int>(Math.floor(player.getY()/32));
  
		std::cout<< "Player Coordinate: " << p.getX() << "  :  " << "Camera coords: "<<view.getCenter().x << std::endl;
		
		view.setSize(sf::Vector2f(width,height));
		if( abs(view.getCenter().x - p.getX()) >= 400 || abs(view.getCenter().y - p.getY()) >= 400 )
		{
			view.setCenter(sf::Vector2f(p.getX(), p.getY()));
		}
  

}
