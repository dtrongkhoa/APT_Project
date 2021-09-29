
#ifndef ASSIGN2_UserMenu_H
#define ASSIGN2_UserMenu_H

#define NEWGAME 1
#define LOADGAME 2
#define CREDITS 3
#define QUIT 4
#define HIDDEN_OPTION 5

#define HELP_PLACE "place <tile> at <position> - place a tile from your hand"
#define HELP_REPLACE "replace <tile> - replace a tile on your hand"
#define HELP_SAVE "save <filename> - save the game to a file (no spaces)"
#define HELP_QUIT "quit - quit the game"

#define OPTION_COUNT 5

// strings representing user prompt actions
#define STR_PLACE "place"
#define STR_REPLACE "replace"
#define STR_SAVE "save"
#define STR_QUIT "quit"

using std::string;
using std::vector;

class UserMenu {

 
    public:
        UserMenu();
        ~UserMenu();
        void showMainMenu();
        string takeTextInput(string message, string error);
        string takeTextInput();
        string takeTextInput(string message);
        int takeNumberInput(int range, string message);
        int takeNumberInput(int range);
        vector<string> getPlayerCommand();
        void printPlayerHelp();   

    private:
        void flushInput();

};


#endif