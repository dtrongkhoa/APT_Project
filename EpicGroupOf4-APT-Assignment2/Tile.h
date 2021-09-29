
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

using std::string;
// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   //Tile constructor
   Tile(Colour, Shape);
   //Tile destructor
   ~Tile();

   //Copy constructor
   Tile(Tile& other);
   Colour getColour();
   Shape getShape();

   Colour colour;
   Shape  shape;

   static bool isValidTileString();
};

#endif // ASSIGN2_TILE_H
