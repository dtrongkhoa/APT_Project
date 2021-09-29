#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Board.h"
#include "TileBag.h"
#include "Player.h"
#include "UserMenu.h"

#include <iostream>
#include <vector>

#define PLAYER_COUNT 2

using std::string;
using std::ifstream;
using std::vector;

class Game {
public:

   Game();
   ~Game();
   void Save(string fileName);
   void Load(string fileName);
   void run();
   void printGameSummary();
   bool isGameOver();
   void setPlayerTurnByIndex(int index);
   void setPlayerTurnByName(string name);
   Player *getCurrentPlayer();
   int getPlayerIndex(string name);
   

private:
   Board* board;
   TileBag* tilebag;
   UserMenu* menu;
   vector<Player*>* players;
   int currentPlayerTurn = 0;

   void showTitle();
   void quit();
   void showCredits();
   void newGame();
   void newGame(int seed);
   void runGame();
   string getPlayerName();
   void printScores();
   bool isValidPlayerName(string name);
   void doPlayerTurn(Player* p);
   
};

#endif // ASSIGN2_GAME_H
