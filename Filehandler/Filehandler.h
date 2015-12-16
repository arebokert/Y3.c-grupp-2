#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../Tools/Matrix.h"

class FileHandler {
public:
	FileHandler() = default;
	FileHandler(const std::string&);
	~FileHandler() = default;
	Matrix& getMap() {return map;};
	void loadMap();
	void loadBlocks();
	void loadPlayer();
	void loadSounds();
	void loadWeapons();
	sf::Texture& getBlock(int) const;
	sf::Texture& getPlayer(int) const;
	sf::Texture& getWeapon(int) const;
	Matrix getArea(int,int,int,int);
	sf::Music& getMusic();
	sf::Sound& getJumpSound();
private:	
	//std::vector<Block> blocks;
	sf::Texture* blocks{nullptr};
	sf::Texture* player{nullptr};
	sf::Texture* weapons{nullptr};
	
	Matrix map;
	std::string projectName;
	//std::vector<std::string> mapNames;
	sf::Music background;
	sf::Sound jumpSound;
	sf::SoundBuffer j_buff;
	sf::Mutex concurrent{};
};

#endif
