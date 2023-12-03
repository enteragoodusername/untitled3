// Note: this comes from a group members project 1 code
#ifndef PROJECT1_COMMANDHANDLER_H
#define PROJECT1_COMMANDHANDLER_H
#include <string>
#include <vector>
#include <regex>
using std::string;
class CommandHandler
{
public:

    static void promptForCommands();
private:
    static void parser(std::string command);
    static std::vector<string> parseArguments(string command);
};


#endif //PROJECT1_COMMANDHANDLER_H
