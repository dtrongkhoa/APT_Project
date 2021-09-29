
#include <fstream>
#include <unistd.h>
#include <string>

#include "Game.h"
#include "Util.h"

Game::Game()
{
   board = new Board();
   menu = new UserMenu();
   players = new vector<Player *>();
}
Game::~Game()
{
   delete board;
   delete menu;
   delete players;
   delete tilebag;
}

//Savefile
void Game::Save(string fileName)
{
   std::ofstream outfile(fileName + ".txt");

   //Save Players' Name, Score and Tiles on hand
   for (Player *p : *players)
   {
      outfile << p->name << std::endl;
      outfile << p->score << std::endl;
      outfile << p->hand->getStr() << std::endl;
   }

   //Save Current Board Sizes
   int currentHeight = board->board.size();
   int currentWidth = board->board[0].size() - 1;
   outfile << currentHeight << "," << currentWidth << std::endl;

   //Save current board state
   int count = 0;
   for (int i = 0; i < currentHeight; i++)
   {
      for (int j = 0; j < currentWidth; j++)
      {
         if (board->board[i][j] != nullptr)
         {
            count++;
            int row_size = i + 65;
            char row_title = (char)row_size;
            if (count == 1)
            {
               outfile << board->board[i][j]->getColour() << board->board[i][j]->getShape() << "@" << row_title << j;
            }
            if (count > 1)
            {
               outfile << ", " << board->board[i][j]->getColour() << board->board[i][j]->getShape() << "@" << row_title << j;
            }
         }
      }
   }

   //Save Current Tile Bag Content
   outfile << std::endl
           << tilebag->getBagContents()->getStr() << std::endl;

   //Save Current Player
   outfile << players->at(currentPlayerTurn)->name << std::endl;

   outfile.close();

   std::cout << "Game successfully saved" << std::endl
             << std::endl;
}

//load file
void Game::Load(string fileName)
{

   string s = " ";
   std::ifstream infile;
   infile.open(fileName + ".txt");

   if (infile.is_open())
   {
      while (!infile.eof())
      {

         std::cout << "Qwirkle game successfully loaded" << std::endl << std::endl;

         string player;
         int score = 0;
         vector<string> tiles;

         for (int line_no = 0; getline(infile, s) && line_no < 10; line_no++)
         {
            // NAME
            //Player 1 name
            if (line_no == 0)
            {
               player = s;
               players->push_back(new Player(player));
            }
            //Player 2 name
            if (line_no == 3)
            {
               player = s;
               players->push_back(new Player(player));
            }

            // SCORE
            //Player 1 score
            if (line_no == 1)
            {
               score = stoi(s);
               Player *p1 = players->at(0);
               p1->score = score;
            }
            //Player 2 score
            if (line_no == 4)
            {
               score = stoi(s);
               Player *p2 = players->at(1);
               p2->score = score;
            }

            // TILES ON HAND
            // Player 1 tiles on hand
            if (line_no == 2)
            {
               tiles = splitString(s, ", ");
               
               for (string s : tiles)
               {
                  Colour colour = s.at(0);
                  Shape shape = s.at(1) - 48;
                  Tile *tile = new Tile(colour, shape);
                  Player *p1 = players->at(0);
                  p1->hand->addBack(tile);
               }
            }

            // Player 2 tiles on hand
            if (line_no == 5)
            {
               tiles = splitString(s, ", ");
               for (string s : tiles)
               {
                  Colour colour = s.at(0);
                  Shape shape = s.at(1) - 48;
                  Tile *tile = new Tile(colour, shape);
                  Player *p2 = players->at(1);
                  p2->hand->addBack(tile);
               }
            }

            // Board size
            // if (line_no == 6){
            // The board size will be 26*26 since the it currently is fixed
            // }

            //Board state
            if (line_no == 7)
            {
               vector<string> states = splitString(s, ", ");
               for (size_t i = 0; i < states.size(); i++)
               {
                  Colour colour = states[i].at(0);
                  Shape shape = states[i].at(1) - 48;
                  Tile *tile = new Tile(colour, shape);
                  string position = states[i].substr(3, 4);
                  board->add(tile, position);
               }
            }

            //Tiles bag content
            if (line_no == 8)
            {
               tiles = splitString(s, ", ");
               tilebag = new TileBag();
               for (size_t i = 0; i < tiles.size(); i++)
               {
                  Colour colour = tiles[i].at(0);
                  int upperCaseStart = 48;
                  Shape shape = tiles[i].at(1) - upperCaseStart;
                  Tile *tile = new Tile(colour, shape);
                  tilebag->list->addBack(tile);
               }
            }

            //current player
            if (line_no == 9)
            {
               Player *currP = players->at(currentPlayerTurn);
               currP->name = s;
            }
         }
         runGame();
      }
      infile.close();
   }
   else
   {
      std::cout << "Not a valid filename!";
   }
}

void Game::run()
{
   showTitle();

   int option = 0;

   while (option != QUIT)
   {
      menu->showMainMenu();
      option = menu->takeNumberInput(OPTION_COUNT, "> ");
      if (option == LOADGAME)
      {
         string message = "Enter the filename from which load a game\n> ";
         string filename = menu->takeTextInput(message);
         Load(filename);
      }
      else if (option == NEWGAME)
         newGame();
      else if (option == CREDITS)
         showCredits();
      else if (option == HIDDEN_OPTION)
      {
         int seed = 1337;
         std::cout << "Starting game with seed: " << seed << std::endl;
         newGame(seed);
      }
   }

   quit();
}

void Game::showTitle()
{
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
}

void Game::quit()
{
   std::cout << "Goodbye\n";
   exit(0);
}

void Game::showCredits()
{
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Name: Eren Yuksel" << std::endl;
   std::cout << "Student ID: S3701484" << std::endl;
   std::cout << "Email: s3701484@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Jun Hong Yeap" << std::endl;
   std::cout << "Student ID: S3696247" << std::endl;
   std::cout << "Email: s3696247@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Martin Jan Medovarsky" << std::endl;
   std::cout << "Student ID: S3842398" << std::endl;
   std::cout << "Email: s3842398@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Trong Khoa Dang" << std::endl;
   std::cout << "Student ID: S3846329" << std::endl;
   std::cout << "Email: s3846329@student.rmit.edu.au" << std::endl;
   std::cout << "----------------------------------" << std::endl;
}

// starts a new game with a random seed.
void Game::newGame()
{
   newGame(0);
}

// starts a new game, with a seed if designated
void Game::newGame(int seed)
{
   std::cout << "Starting a New Game"<< std::endl
             << std::endl;

   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      std::cout << "Enter player " << i + 1;
      std::cout << " name (uppercase characters only) " << std::endl;
      string name = getPlayerName();
      players->push_back(new Player(name));
   }

   std::cout << "Let's Play!" << std::endl
             << std::endl;

   tilebag = new TileBag();
   tilebag->populateBag();
   // if the seed is 0, we'll shuffle
   // the tilebag randomly
   if (seed == 0)
      tilebag->shuffleBag();
   else
      tilebag->shuffleBag(seed);

   // fill each players hand with six tiles
   for (Player *p : *players)
      for (int num = 0; num < 6; num++)
         p->hand->addFront(tilebag->takeFromBag());

   runGame();
}

void Game::runGame()
{

   while (!isGameOver())
   {
      // it would probably look better if we cleared the terminal each turn
      // but we'll keep it this way as it's not mentioned in the spec
      Player *p = players->at(currentPlayerTurn);
      std::cout << p->name << ", it's your turn" << std::endl;
      printScores();
      board->printBoard();
      std::cout << "Your hand is:" << std::endl;
      if (p->hand->getSize() == 0)
         std::cout << "Empty!";
      else
         p->hand->printNodes();

      std::cout << std::endl;

      doPlayerTurn(p);

      // modulo is here because it keeps everything clean.
      currentPlayerTurn = (currentPlayerTurn + 1) % PLAYER_COUNT;
   }

   std::cout << "Game over\n";
   printGameSummary();

   quit();
}

void Game::printGameSummary()
{
   int highestScore = -1;
   Player *winner;

   for (Player *p : *players)
   {
      std::cout << "Score for " << p->name << ": " << p->score;
      if (p->score > highestScore)
      {
         highestScore = p->score;
         winner = p;
      }
   }
   std::cout << "Player " << winner->name << "won!\n";
}

bool Game::isGameOver()
{
   if (tilebag->getBagContents()->getSize() == 0)
      for (Player *p : *players)
         if (p->hand->getSize() == 0)
         {
            // Qwirkle rule:
            // 6 is added to the score of the player who
            // loses their tiles first.
            p->score += 6;
            return true;
         }

   return false;
}

void Game::setPlayerTurnByIndex(int index)
{
   currentPlayerTurn = index % PLAYER_COUNT;
}

void Game::setPlayerTurnByName(string name)
{
   currentPlayerTurn = getPlayerIndex(name) % PLAYER_COUNT;
}

Player *Game::getCurrentPlayer()
{
   return players->at(currentPlayerTurn % PLAYER_COUNT);
}

// gets a players index in the list by their name
int Game::getPlayerIndex(string name)
{
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      if (players->at(i)->name == name)
         return i;
   }

   return 0;
}

string Game::getPlayerName()
{
   bool validName = false;
   string name = "";
   // get a valid name string (uppercase letters and spaces only)
   while (!validName)
   {
      name = menu->takeTextInput("> ");
      validName = isValidPlayerName(name);
      if (!validName)
      {
         string errormsg = "Uppercase letters only, no numbers or symbols.";
         std::cout << errormsg << std::endl;
      }
      else
      {
         // check if the converted name is a duplicate
         // of another players name
         for (Player *p : *players)
            if (name == p->name)
               validName = false;

         if (!validName)
         {
            string errormsg = "This name is already taken! Please try another";
            std::cout << errormsg << std::endl;
         }
      }
   }

   return name;
}

void Game::printScores()
{
   for (Player *p : *players)
   {
      std::cout << "Score for " << p->name;
      std::cout << ": " << p->score << std::endl;
   }
}

void Game::doPlayerTurn(Player *p)
{
   bool hasTurn = true;
   while (hasTurn)
   {
      vector<string> command = menu->getPlayerCommand();
      string base = command.at(0);
      if (base == STR_SAVE)
      {
         string filename;
         // create the filename exactly as they typed it
         // filling in any spaces they may typed.
         for (size_t i = 1; i < command.size(); i++)
         {
            filename += command.at(i);
            if (i != command.size() - 1)
               filename += " ";
         }

         Save(filename);
      }
      else if (base == STR_PLACE)
      {
         string tile = command.at(1);
         string posStr = command.at(3);

         int tileIndex = p->hand->contains(tile);

         bool isValidTile = (tileIndex != -1);
         bool isValidPosition = Board::isValidPosition(posStr);

         // check if the tile, board position are valid,
         // and check if the move is legal.
         // then, copy the tile in the hand for the board,
         // and remove it from the hand!

         // and print appopriate error messages.

         if (!isValidTile)
         {
            std::cout << "That tile doesn't exist in your hand!" << std::endl;
         }
         else if (!isValidPosition)
         {
            std::cout << "That position is invalid!" << std::endl;
         }
         else if (isValidTile && isValidPosition)
         {
            Tile *t = p->hand->get(tileIndex);
            int *pos = Board::getPositionFromStr(posStr);

            bool isValidMove = board->isValidMove(t, pos[0], pos[1]);
            if (isValidMove)
            {
               board->add(new Tile(*t), posStr);
               p->hand->remove(tileIndex);
               p->score += board->getScore();

               Tile *bagTile = tilebag->takeFromBag();
               if (bagTile != nullptr)
                  p->hand->addBack(bagTile);

               hasTurn = false;
            }
            else
               std::cout << "You can't place that there! Try something else." << std::endl;
         }
      }
      else if (base == STR_REPLACE)
      {
         // check if the hand contains the specified tile,
         // create a copy for the tilebag, and remove it from the hand
         int tileIndex = p->hand->contains(command.at(1));
         if (tileIndex == -1)
         {
            std::cout << "You don't have that tile in your hand!" << std::endl;
         }
         else
         {

            Tile *newTile = tilebag->takeFromBag();
            Tile *oldTile = p->hand->get(tileIndex);

            tilebag->addToBag(new Tile(*oldTile));
            p->hand->remove(tileIndex);

            if (newTile != nullptr)
               p->hand->addBack(newTile);

            hasTurn = false;
         }
      }
      else if (base == STR_QUIT)
         quit();
   }
}

bool Game::isValidPlayerName(string name)
{
   // check if a character is something other than
   // space, and the alphabet, and return false if so.

   // grab the char codes for the allowed characters
   // or character sets.
   int space = 32;
   int ucase = 65; // first uppercase char

   for (unsigned int i = 0; i < name.length(); i++)
   {
      int charCode = (int)name.at(i);

      // check if the character is not a space, then
      // if it is outside the bounds of the uppercase
      // english alphabet
      if (charCode != space)
      {
         bool isBelowUpper = charCode < ucase;
         bool isAboveUpper = charCode >= ucase + 26;

         if (isBelowUpper || isAboveUpper)
            return false;
      }
   }

   return true;
}