#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#define MAX_ROW 26
#define MAX_COL 26

#include <vector>
#include "Tile.h"
#include <string>

class Board{

public:

    Board();
    ~Board();
    void add(Tile* tile, std::string position);
    void printBoard();
    bool isValidMove(Tile* copyTile, int row_index, int col_index);
    int getScore();
    
    // checks if a position is valid (within range of
    // the boards rows and columns, NOT if a move is legal, 
    // that's what isValidMove is for)
    static bool isValidPosition(string pos);
    static bool isValidPosition(int row, int column);
    static int* getPositionFromStr(string pos);

    std::vector<std::vector<Tile* > > board;
    

private:

    int score;
    bool isEmpty();
    int calculateScore(int row, int col);
    
};



#endif //ASSIGN2_BOARD_H
