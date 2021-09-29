
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>
using std::string;

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   //Methods to add node to head / tail
   void addFront(Tile* data);
   void addBack(Tile* data);

   //returns size
   int getSize();
   //Given an index returns the tile present
   Tile* get(int index);

   //Returns a string containing all tiles in the linked list
   string getStr();

   //removes the front (head) element
   void removeFront();

   //Removes a node at a particular index
   void remove(int index);

   // Returns the index of a tile matching the given string
   // in the list.
   int contains(string tile);

   //Removes tile corresponding with given string code
   //eg. "R2"
   void removeByStr(string code);
   
   void clear();
   void printNodes();


private:
   Node* head;
   //Size of the list. Updated on each addition / removal.
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
