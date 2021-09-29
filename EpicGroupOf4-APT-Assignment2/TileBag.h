#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "Tile.h"
#include "LinkedList.h"
#include "TileCodes.h"

#define BAG_SIZE 72

class TileBag {
    public: 
        TileBag();
        ~TileBag();
        void populateBag();
        void populateBag(int num);
        void shuffleBag();
        void shuffleBag(int seed);
        Tile* takeFromBag();
        Tile* addToBag(Tile* t);
        LinkedList* getBagContents();
        LinkedList* list;

    private:
       

};

#endif