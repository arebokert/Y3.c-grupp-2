#include <fstream>
#include <thread>
#include <iostream>
#include <string>
#include "Filehandler.h"
#include "../Tools/Matrix.h"
#include <SFML/Graphics.hpp>

using namespace std;

/*
  Filsystem:
  1. Projekt fil: Innehåller namn till filer för Maps, Blocks etc
  2. Map: Innehåller namn till alla xx.map filer
  3. xx.map: Namn, Storlek, Block matrix
  4. Block: Innehåller antalet blocks samt namn för varje bild till blocken

*/

FileHandler::FileHandler(const string& project) {
  projectName = project;
  //Skapa threads för alla load funktioner
  //Thread-safe, read-only
  thread t1(&FileHandler::loadMap, this);
  thread t2(&FileHandler::loadBlocks, this);
  
  //Vänta på threads med thread.join()
  t1.join();
  t2.join();
}

void FileHandler::loadMap() {
  //1. Läs in antal maps i projektet
  //2. Loop
  //2.1. Läs in första namnet
  //2.2. Läs in storlek
  //2.3. Läs in Matrix
  //2.4. Skapa Map(storlek, namn, Matrix)
  //2.5. Lägg in Map i vectorn
  ifstream input;
  input.open("Data/Maps/test");
  
  int width;
  int height;
  if(!input) {
	cerr << "Error loading file info.txt" << endl;
  }
  else {
    
    input >> width;
    cout << width << endl; 
    input >> height;
    cout << height << endl;
    map = Matrix{width,height};
    for(int i = 0; i < width; i++)
      for(int j = 0; j < height; j++) {
		input >> map.at(i,j);
      }
  }
 

  
  
}
 

void FileHandler::loadBlocks() {
  //1. Läs in antalet blocks
  //2. Loop
  //2.1. Ladda in namn
  //2.2. Skapa block
  //2.3. Tilldela block bild från namn
  //2.4. Lägg in block i vectorn
  ifstream input;
  input.open("Data/Blocks/test");

  blocks = new sf::Texture[16];
  string s{"Data/Blocks/"};
  for(int i = 1; i <= 15; i++) {

    s.append(to_string(i));
    s.append(".png");
  if(!blocks[i-1].loadFromFile(s))
    cout << "Couldn't load block: " << i << endl;
  else
    cout << "Loaded block: " << i << endl;
  s = "Data/Blocks/";
  }
  
}


sf::Texture& FileHandler::getBlock(int i) const {
  return blocks[i];
}


Matrix FileHandler::getArea(int x1, int y1, int x2, int y2)  {
  return map.getArea(x1,y1,x2,y2);
}
