#include "Camera.h"

void Camera::update(Player& p) {
  
  //Check where player is in the Array-coordinate system
  // x = static_cast<int>(Math.floor(player.getX()/32));
  // y = static_cast<int>(Math.floor(player.getY()/32));
  
  view.setCenter(sf::Vector2f(p.getX(), p.getY()));
  view.setSize(sf::Vector2f(width,height));
  
}
