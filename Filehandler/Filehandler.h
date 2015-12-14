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
	sf::Texture& getBlock(int) const;
	sf::Texture& getPlayer(int) const;
	Matrix getArea(int,int,int,int);
	sf::Music& getMusic();
	sf::Sound& getJumpSound();
private:	
	//std::vector<Block> blocks;
	sf::Texture* blocks{nullptr};
	sf::Texture* player{nullptr};
	
	Matrix map;
	std::string projectName;
	//std::vector<std::string> mapNames;
	sf::Music background;
	sf::Sound jumpSound;
	sf::SoundBuffer j_buff;
	sf::Mutex concurrent{};
};

#endif
