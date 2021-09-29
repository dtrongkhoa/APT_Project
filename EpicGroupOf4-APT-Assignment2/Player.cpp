#include "Player.h"

Player::Player(string name){
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
}

Player::~Player(){
}
