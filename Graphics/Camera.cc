#include "Camera.h"
#include <iostream>
#include <math.h>
void Camera::update(Player& p) {
  
  //Check where player is in the Array-coordinate system
  // x = static_cast<int>(Math.floor(player.getX()/32));
  // y = static_cast<int>(Math.floor(player.getY()/32));
  
		
		
		view.setSize(sf::Vector2f(width,height));
		if((view.getCenter().x - p.getX()) >= 200)
		{
			view.setCenter(sf::Vector2f(p.getX()+200,view.getCenter().y));
		}
		else if ((p.getX() - view.getCenter().x) >= 200)
		{
			view.setCenter(sf::Vector2f(p.getX()-200, view.getCenter().y));
		}
		
		if((view.getCenter().y - p.getY()) >= 200)
		{
			view.setCenter(sf::Vector2f(view.getCenter().x, p.getY()+200));
		}
		else if ((p.getY() - view.getCenter().y) >= 200)
		{
			view.setCenter(sf::Vector2f(view.getCenter().x, p.getY()-200));
		}
  

}
