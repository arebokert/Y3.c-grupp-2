#include <fstream>
#include <thread>
#include <iostream>
#include <string>
#include "Filehandler.h"
#include "../Tools/Matrix.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
  //Create threads for each load function
  //Thread-safe, read-only
  thread t1(&FileHandler::loadMap, this);
  thread t2(&FileHandler::loadBlocks, this);
  thread t3(&FileHandler::loadPlayer, this);
  thread t4(&FileHandler::loadSounds, this);
  thread t5(&FileHandler::loadMonster, this);

  //Vänta på threads med thread.join()
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  //Loading player seperately due to hardware concurrency
  //loadPlayer();
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
  input.open("Data/Maps/Fieldtest1");
  
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
  
  concurrent.lock();
  blocks = new sf::Texture[16];
  concurrent.unlock();

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

void FileHandler::loadPlayer() {

  concurrent.lock();
  player = new sf::Texture[8];
  concurrent.unlock();

  string s{"Data/Player/"};

  for(int i{0}; i < 8; i++) {

    s.append(to_string(i));
    s.append(".png");
    cout << s << endl;
    
    if(!player[i].loadFromFile(s))
      cout << "Couldn't load playerTex: " << i << endl;
    else
      cout << "Loaded playerTex: " << i << endl;
    
    s = "Data/Player/";
   }
  
}

void FileHandler::loadMonster() {
  concurrent.lock();
  monster = new sf::Texture[6];
  concurrent.unlock();

  string s{"Data/Monster/"};

  for(int i{0}; i <= 5; i++) {

    s.append(to_string(i));
    s.append(".png");
    cout << s << endl;
   
    if(!monster[i].loadFromFile(s))
      cout << "Couldn't load MonsterTex: " << i << endl;
    else
      cout << "Loaded MonsterTex: " << i << endl;
    
    s = "Data/Monster/";
   }  
}


void FileHandler::loadSounds() {
  background.setVolume(30);
  background.setLoop(true);

  if(!background.openFromFile("Data/Sounds/SummerLight.ogg"))
    cerr << "Unable to load music file" << endl;

  if(!j_buff.loadFromFile("Data/Sounds/jump.ogg"))
    cerr << "Unable to load jump sound file" << endl;

  jumpSound.setBuffer(j_buff);
  jumpSound.setVolume(100);
  jumpSound.setPitch(0.8);
}

void FileHandler::loadWeapons() {
	concurrent.lock();
	weapons = new sf::Texture[6];
	concurrent.unlock();

	string s{"Data/Weapons/"};

	for(int i{0}; i <= 5; i++) {

		s.append(to_string(i));
		s.append(".png");
		cout << s << endl;
   
		if(!weapons[i].loadFromFile(s))
			cout << "Couldn't load WeaponTex: " << i << endl;
		else
			cout << "Loaded WeaponTex: " << i << endl;
    
		s = "Data/Weapons/";
   }
}

sf::Texture& FileHandler::getBlock(int i) const {
  return blocks[i];
}

sf::Texture& FileHandler::getPlayer(int i) const {
  return player[i];
}
sf::Texture& FileHandler::getMonster(int i) const {
  return monster[i];
}

sf::Texture& FileHandler::getWeapon(int i) const {
  return weapons[i];
}

Matrix FileHandler::getArea(int x1, int y1, int x2, int y2)  {
  return map.getArea(x1,y1,x2,y2);
}

sf::Music& FileHandler::getMusic() {
  return background;
}

sf::Sound& FileHandler::getJumpSound() {
  return jumpSound;
}
