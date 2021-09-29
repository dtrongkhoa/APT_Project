#include <iostream>
#include <cstring>
#include <limits>
#include <vector>

#include "UserMenu.h"
#include "Util.h"

using std::string;
using std::vector;

UserMenu::UserMenu() {}

UserMenu::~UserMenu() {}

void UserMenu::showMainMenu()
{
    std::cout << std::endl;
    std::cout << "Menu" << std::endl
              << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (show student info)" << std::endl;
    std::cout << "4. Quit" << std::endl
              << std::endl;
}

// takes ANY text input and returns it.
// with an optional prefix
string UserMenu::takeTextInput(string message, string error)
{

    string input;
    bool invalid = true;
    do
    {
        if (!message.empty())
            std::cout << message;

        flushInput();
        getline(std::cin, input);

        invalid = (input.empty());
        if (invalid)
            if (!error.empty())
                std::cout << error << std::endl;

    } while (invalid);

    std::cout << std::endl;
    return input;
}

string UserMenu::takeTextInput()
{
    return takeTextInput("");
}

string UserMenu::takeTextInput(string message)
{
    return takeTextInput(message, "\nInvalid input. Please try again.");
}

// takes a numerical input, from 1 to *range* inclusive
int UserMenu::takeNumberInput(int range, string message)
{

    int option = 0;
    string input;
    bool invalid = true;
    do
    {

        if (!message.empty())
            std::cout << message;
        // we read a string and do integer conversion, rather than
        // reading an integer directly, as that causes more problems
        // with stdin buffer and reading values it shouldn't.
        flushInput();
        getline(std::cin, input);
        option = atoi(input.c_str());

        invalid = (option > range || option <= 0);

        if (invalid)
        {
            std::cout << "Please input a number between 1 and ";
            std::cout << range << "." << std::endl;
        }

    } while (invalid);

    std::cout << std::endl;
    return option;
}

int UserMenu::takeNumberInput(int range)
{
    return takeNumberInput(range, "");
}

// so we can read from cin without worrying about
// previous inputs being read incorrectly
void UserMenu::flushInput()
{
    std::cin.clear();
    fflush(stdin);
}

vector<string> UserMenu::getPlayerCommand()
{
    vector<string> VALID_COMMANDS = {STR_REPLACE, STR_PLACE, STR_SAVE, STR_QUIT};

    vector<string> cmd;
    bool isValidCommand = false;
    while (!isValidCommand)
    {
        string input = takeTextInput("> ");
        cmd = splitString(input, " ");

        // base command (e.g for 'replace G6' it is 'replace')
        string b = cmd.at(0);

        bool replace = b == STR_REPLACE && cmd.size() == 2;
        bool place = b == STR_PLACE && cmd.size() == 4 && cmd.at(2) == "at";
        bool save = b == STR_SAVE && cmd.size() >= 2;
        bool quit = b == STR_QUIT;

        isValidCommand = replace || save || place || quit;

        if (!isValidCommand)
        {
            std::cout << "Invalid command. Please enter a command:" << std::endl;
            printPlayerHelp();
        }
    }

    return cmd;
}

void UserMenu::printPlayerHelp()
{
    std::cout << "  " << HELP_PLACE << std::endl;
    std::cout << "  " << HELP_REPLACE << std::endl;
    std::cout << "  " << HELP_SAVE << std::endl;
    std::cout << "  " << HELP_QUIT << std::endl;
    std::cout << "All commands are case-sensitive." << std::endl;
}
