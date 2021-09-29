#include "Board.h"
#include <vector>
#include <iostream>
#include <string>

Board::Board()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        std::vector<Tile *> temp;
        for (int j = 0; j < MAX_COL + 1; j++)
        {
            temp.push_back(nullptr);
        }
        board.push_back(temp);
    }
    score=0;
}

Board::~Board()
{
}
void Board::add(Tile *tile, std::string position)
{
    Tile *copyTile = new Tile(*tile);
    if (position.length() >= 2)
    {
        char row = position.at(0);
        int row_index = (int)row - 65;
        int col_index = std::stoi(position.substr(1, position.length()));

        if (isValidMove(copyTile, row_index, col_index))
        {
            for (int i = 0; i < MAX_ROW; i++)
            {
                for (int j = 0; j < MAX_COL; j++)
                {
                    if (i == row_index && j == col_index)
                    {
                        board[i][j] = copyTile;
                        score = calculateScore(row_index, col_index);
                    }
                }
            }
        }
    }
}

void Board::printBoard()
{
    for (int i = 0; i < MAX_COL + 1; i++)
    {
        if (i == 0)
        {
            std::cout << "   ";
        }
        else if (i <= 10)
        {
            std::cout << " " << i - 1 << " ";
        }
        else
        {
            std::cout << i - 1 << " ";
        }
    }
    std::cout << std::endl;

    for (int i = 0; i < MAX_COL + 1; i++)
    {
        if (i == 0)
        {
            std::cout << "  ";
        }
        else
        {
            std::cout << "---";
        }
    }
    std::cout << std::endl;

    char start = 'A';
    for (int i = 0; i < MAX_ROW; i++)
    {
        std::cout << start << " |";
        for (int j = 0; j < MAX_COL; j++)
        {
            if (board[i][j] != nullptr)
            {
                std::string tile;
                tile.push_back(board[i][j]->colour);
                tile = tile + std::to_string(board[i][j]->shape);
                std::cout << tile << "|";
            }
            else
            {
                std::cout << "  |";
            }
        }
        std::cout << std::endl;
        start++;
    }
}

bool Board::isEmpty()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            if (board[i][j] != nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::isValidMove(Tile *copyTile, int row_index, int col_index)
{
    bool isAvailable = true;
    //Check Max Range
    if (row_index >= 0 && row_index < MAX_ROW)
    {
        if (col_index >= 0 && col_index < MAX_COL)
        {

            //Check Board is not Empty
            if (!isEmpty())
            {

                // check if there isn't a tile here already
                if (board[row_index][col_index] != nullptr)
                    return false;
                for (int i = 1; i < 6; i++)
                {
                    // CHECK LEFT TILES
                    if (col_index - i >= 0)
                    {
                        Tile *leftTile = board[row_index][col_index - i];
                        if ((leftTile != nullptr) && (((copyTile->getShape() != leftTile->getShape()) && (copyTile->getColour() != leftTile->getColour())) || ((copyTile->getShape() == leftTile->getShape()) && (copyTile->getColour() == leftTile->getColour()))))
                        {
                            isAvailable = false;
                        }
                    }
                    //CHECK RIGHT TILES
                    if (col_index + i < MAX_COL)
                    {
                        Tile *rightTile = board[row_index][col_index + i];
                        if ((rightTile != nullptr) && (((copyTile->getShape() != rightTile->getShape()) && (copyTile->getColour() != rightTile->getColour())) || ((copyTile->getShape() == rightTile->getShape()) && (copyTile->getColour() == rightTile->getColour()))))
                        {
                            isAvailable = false;
                        }
                    }
                    //CHECK UP TILES
                    if (row_index - i >= 0)
                    {
                        Tile *upTile = board[row_index - i][col_index];
                        if ((upTile != nullptr) && (((copyTile->getShape() != upTile->getShape()) && (copyTile->getColour() != upTile->getColour())) || ((copyTile->getShape() == upTile->getShape()) && (copyTile->getColour() == upTile->getColour()))))
                        {
                            isAvailable = false;
                        }
                    }
                    //CHECK DOWN TILES
                    if (row_index + i < MAX_ROW)
                    {
                        Tile *downTile = board[row_index + i][col_index];
                        if ((downTile != nullptr) && (((copyTile->getShape() != downTile->getShape()) && (copyTile->getColour() != downTile->getColour())) || ((copyTile->getShape() == downTile->getShape()) && (copyTile->getColour() == downTile->getColour()))))
                        {
                            isAvailable = false;
                        }
                    }
                }
            }
            else
            {
                isAvailable = true;
            }
        }
        else
        {
            isAvailable = false;
        }
    }
    else
    {
        isAvailable = false;
    }
    return isAvailable;
}

int Board::calculateScore(int row, int col)
{
    int newScore = 0;
    int count_left = 0;
    int count_right = 0;
    int count_up = 0;
    int count_down = 0;
    //Calculate the number of left tiles
    if (col - 1 >= 0)
    {
        Tile *leftTile = board[row][col - 1];
        int i = 2;
        while (leftTile != nullptr && count_left < 6)
        {
            count_left++;
            if (col - i >= 0)
            {
                leftTile = board[row][col - i];
                i++;
            }
            else
            {
                leftTile = nullptr;
            }
        }
    }
    //Calculate the number of right tiles
    if (col + 1 < MAX_COL)
    {
        Tile *rightTile = board[row][col + 1];
        int i = 2;
        while (rightTile != nullptr && count_right < 6)
        {
            count_right++;
            if (col + i < MAX_COL)
            {
                rightTile = board[row][col + i];
                i++;
            }
            else
            {
                rightTile = nullptr;
            }
        }
    }
    //Calculate score for left and right tiles.
    newScore = newScore + count_left + count_right;
    //Check Qwirkle
    if ((count_left + count_right + 1) == 6)
    {
        newScore += 6;
        std::cout << "QWIRKLE!!!" << std::endl;
    }
    //UP-DOWN
    //Calculate the number of below tiles
    if (row - 1 >= 0)
    {
        Tile *upTile = board[row - 1][col];
        int i = 2;
        while (upTile != nullptr && count_up < 6)
        {
            count_up++;
            if (row - i >= 0)
            {
                upTile = board[row - i][col];
                i++;
            }
            else
            {
                upTile = nullptr;
            }
        }
    }
    //Calculate the number of below tiles
    if (row + 1 < MAX_ROW)
    {
        Tile *downTile = board[row + 1][col];
        int i = 2;
        while (downTile != nullptr && count_down < 6)
        {
            count_down++;
            if (row + i < MAX_ROW)
            {
                downTile = board[row + i][col];
                i++;
            }
            else
            {
                downTile = nullptr;
            }
        }
    }
    //Calculate score for above and below tiles.
    newScore = newScore + count_up + count_down;
    //Check qwirkle
    if ((count_up + count_down + 1) == 6)
    {
        newScore += 6;
        std::cout << "QWIRKLE!!!" << std::endl;
    }
    //Add score for itself in row
    if (count_left != 0 || count_right != 0)
    {
        newScore++;
    }
    //Add score for itself in col
    if (count_up != 0 || count_down != 0)
    {
        newScore++;
    }
    //Add score for first tile
    if (count_left == 0 && count_right == 0 && count_up == 0 && count_down == 0)
    {
        newScore++;
    }

    return newScore;
}
int Board::getScore()
{
    return this->score;
}

bool Board::isValidPosition(string pos)
{
    int ucaseStart = 65;

    int row = (int)pos.at(0) - ucaseStart;
    int column = atoi(pos.substr(1).c_str());

    if (row < 0 || row >= MAX_ROW)
        return false;
    if (column < 0 || column >= MAX_COL)
        return false;

    return true;
}

bool Board::isValidPosition(int row, int column)
{
    if (row < 0 || row >= MAX_ROW)
        return false;
    if (column < 0 || column >= MAX_COL)
        return false;

    return true;
}

int *Board::getPositionFromStr(string pos)
{
    int ucaseStart = 65;

    int row = (int)pos.at(0) - ucaseStart;
    int column = atoi(pos.substr(1).c_str());

    if (isValidPosition(row, column))
        return new int[2]{row, column};
    else
        return nullptr;
}