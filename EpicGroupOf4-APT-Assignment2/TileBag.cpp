#include <stdlib.h>
#include <time.h>
#include "TileBag.h"

TileBag::TileBag(){

    list = new LinkedList();

}

TileBag::~TileBag() {
}

void TileBag::populateBag()
{
    populateBag(BAG_SIZE);
}

void TileBag::populateBag(int num)
{
    
    Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int UNIQUE_PER_CATEGORY = 6;

    // add a set of tiles to the bag, then check if we're
    // above the tilecount

    // note: it'll add full sets, it won't add partial sets,
    // so bag size will always be a multiple of 36
    int i = 0;
    while(i < num){
        for (int j = 0; j < UNIQUE_PER_CATEGORY; j++)
            for (int k = 0; k < UNIQUE_PER_CATEGORY; k++){
                list->addFront(new Tile(colours[k], j+1));
                i++;
            }
            
        
    }
    
}

void TileBag::shuffleBag()
{
    // shuffle bag with a 'random' seed (epoch time in seconds)
    srand(time(0));
    shuffleBag(rand());
}

void TileBag::shuffleBag(int seed)
{
    
    int size = list->getSize();

    Tile* tiles[size];

    // shuffle the bag by copying each entry 
    // into an array, then moving each entry 
    // into a new position using the seed given
    // note: we copy so that we can delete the old 
    // list safely
    
    // copy all tiles
    for (int i = 0; i < size; i++){
        tiles[i] = new Tile(*list->get(i));    
    }

    // shuffle them around
    for (int i = 0; i < size; i++){
        // modulus INT_MAX so we 
        // don't overflow to a signed int
        srand((i + seed) % 2147483648);
        int newPos = rand() % size;
        Tile* t1 = tiles[i];
        Tile* t2 = tiles[newPos];
        
        tiles[newPos] = t1;
        tiles[i] = t2;
    }

    delete list;
    // create a new linked list, and add all the tiles to it.
    this->list = new LinkedList();

    for (int i = 0; i < size; i++)
        list->addFront(tiles[i]);

}

// take the top (or front) tile from a bag.
Tile* TileBag::takeFromBag()
{
    if (list->getSize() == 0) return nullptr;
    Tile* t = new Tile(*list->get(0));
    list->removeFront();
    return t;
}

Tile* TileBag::addToBag(Tile* t)
{
    list->addFront(t);
    return t;
}

LinkedList* TileBag::getBagContents()
{
    return list;
}
