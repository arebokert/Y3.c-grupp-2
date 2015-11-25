#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Tools/Matrix.h"

class FileHandler {
public:
	FileHandler() = default;
	FileHandler(const std::string&);
	~FileHandler() = default;
	Matrix& getMap() {return map;};
	void loadMap();
	void loadBlocks();
	sf::Texture& getBlock(int) const;
	Matrix getArea(int,int,int,int);
private:	
	//std::vector<Block> blocks;
	sf::Texture* blocks{nullptr};
	//std::vector<Map> maps;
	Matrix map;
	std::string projectName;
	//std::vector<std::string> mapNames;
};

#endif
