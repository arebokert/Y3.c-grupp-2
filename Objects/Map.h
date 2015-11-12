#ifndef MAP_H
#define MAP_H

class Map {
public:
	Map(int, int);
	~Map() = default;
	int* getMap();
private:
	int mapLayer[0][0];
};

#endif
