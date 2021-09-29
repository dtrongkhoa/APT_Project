#ifndef ASSIGN2_Player_H
#define ASSIGN2_Player_H

#include "LinkedList.h"
#include <string>

using std::string;

class Player{
public:

Player(string name);
~Player();

//Linked list of the player's hand, containing their tiles.
LinkedList* hand;
string name;
int score;

};

#endif // ASSIGN2_Player_H
