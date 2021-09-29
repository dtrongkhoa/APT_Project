
#include "LinkedList.h"
//for testing purposes, need to remove
#include <iostream>

//Constructor
LinkedList::LinkedList()
{
   head = nullptr;
   size = 0;
}

//Destructor
LinkedList::~LinkedList() {
   this->clear();
}

void LinkedList::addFront(Tile *data)
{
   //Using tile to create new node

   //Creating a deep copy of tile when adding it to LinkedList
   Node* node = new Node(new Tile(*data), head);
   //Setting the linked list head to the new node
   this->head = node;
   this->size++;
}

void LinkedList::addBack(Tile *data)
{
   if (data == nullptr)
      return;

   this->size++;
   if (head == nullptr){
      head = new Node(data, nullptr);
      return;
   } 
   
   Node* n = head;
   Node* prev;

   
   while (n != nullptr){
      prev = n;
      n = n->next;
   }

   prev->next = new Node(data, nullptr);

}

//Returns the list's size.
int LinkedList::getSize()
{
   return this->size;
}

//Returns the tile present at a given index
Tile *LinkedList::get(int index)
{
   Tile *retTile = nullptr;

   int listSize = getSize();

   if (index >= 0 && index < listSize)
   {
      Node *current = head;

      //Loop through list until index is reached
      for (int i = 0; i < index; i++)
      {
         current = current->next;
      }

      retTile = current->tile;
   }
   return retTile;
}

string LinkedList::getStr()
{

   string strList = "";

   Node *current = head;

   bool endList = false;

   //Loop through linked list
   while (endList == false)
   {

      Tile *currTile = current->tile;

      strList += currTile->colour;
      strList += std::to_string(currTile->shape);

      current = current->next;

      if (current == nullptr)
      {
         endList = true;
      }
      else
      {
         strList += ", ";
      }
   }
   return strList;
}

void LinkedList::removeFront()
{
   if (head != nullptr)
   {
      Node *removed = head;
      head = head->next;

      delete removed->tile;
      delete removed;
   } //Maybe add an else here

   this->size--;
}

//Removes a node at a particular index
void LinkedList::remove(int index)
{
   if (index >= 0 && index < size)
   {
      if (head != nullptr)
      {
         Node *current = head;
         //pre should point to node before current;
         Node *prev = nullptr;

         for (int i = 0; i < index; i++)
         {
            prev = current;
            current = current->next;
         }

         if (prev == nullptr)
         {
            head = current->next;
         }
         else
         {
            prev->next = current->next;
         }

         delete current->tile;
         delete current;
         this->size--;
      }
   }
}

// gets the index of a tile matching the string input 
// if no tile is found, returns -1
int LinkedList::contains(string code)
{
   //Used to help convert char to int
   int asciiDiff = 48;

   char color = code[0];
   int shape = code[1] - asciiDiff;

   Node *current = head;

   int index = 0;
   bool endList = false;
   //Loop through linked list
   while (endList == false)
   {
      //Check for matching tile
      Tile *currTile = current->tile;
      if (currTile->colour == color && currTile->shape == shape)
         return index;
      current = current->next;
      if (current == nullptr)
         endList = true;

      index++;
   }

   return -1;
}

//Removes tile corresponding with given string code
//eg. "R2". Does nothing if given incorrect input
void LinkedList::removeByStr(string code)
{
   int index = contains(code);
   if (index != -1)
      remove(index);
}

//Removes every element from the list
void LinkedList::clear()
{
   while (head != nullptr)
   {
      removeFront();
   }
}

void LinkedList::printNodes()
{
   Node* current = head;

   for (int i = 0; i < size; i++)
   {
      Tile* t = current->tile;
      std::cout << t->getColour() << t->getShape();
      current = current->next;
      if (current != nullptr)
         std::cout << ",";
   }
}