#ifndef MAP_H
#define MAP_H

#include "game.h"
#include <string>
#include "ECS/Components.h"

class Map
{
public:
    Map(const char* mfp, int ms, int ts);
    ~Map();

    void loadMap(std::string path, int sizeX, int sizeY);
    void addTile(int srcX, int srcY, int xpos, int ypos);
private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};

#endif // MAP_H
