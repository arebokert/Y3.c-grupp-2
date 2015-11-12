#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Filehandler.h"

void hello() {
  std::cout << "Hello: " << std::this_thread::get_id() << std::endl;
}

int main() {
  std::thread t(hello);
  t.join();
  FileHandler fh{"Test"};
  sf::Texture tex{fh.getBlock(1)};
  return 0;
}
