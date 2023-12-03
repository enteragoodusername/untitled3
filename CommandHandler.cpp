// Note: this comes from a group members project 1 code
#include <regex>
#include "CommandHandler.h"
#include <iostream>
#include <sstream>
using std::string;
using std::cout;
using std::cin;


// parses command line in order to choose proper command, also verifies that id and name have appropriate syntax
 void CommandHandler::parser(string command) {
     std::vector<string> arguments = CommandHandler::parseArguments(command);
}

// returns all arguments in command line as a vector of strings
std::vector<string> CommandHandler::parseArguments(string command){
     std::regex argumentGrabber = std::regex("(?!\\S+[ ]{0,}).+");
     std::regex argumentDeleter = std::regex("^\\S+[ ]{0,}");
     std::regex argumentDeleterQuotations =std::regex("(\")(?!\\S+[ ]{0,}).+");


     std::vector<string> arguments;
    while (command != ""){
        // to deal with the case quotation marks contain text
        if ('\"' == *command.begin()){
            bool isOtherMarkFound = false;
            string inQuotes = "";
            for (int i = 1; i < int(command.length()); i++){
                if (command[i] == '\"'){
                    isOtherMarkFound = true;
                    command = command.substr(i + 1,command.length()-i);
                    break;
                }
                inQuotes += command[i];
            }
            if (isOtherMarkFound){
                arguments.push_back(inQuotes);
                command = std::regex_replace(command,std::regex("^[ ]{0,}"),"");
            }
            else{
                arguments.push_back(std::regex_replace(command,argumentGrabber,""));
                command = std::regex_replace(command,argumentDeleter,"");
            }

        }
        else{
            arguments.push_back(std::regex_replace(command,argumentGrabber,""));
            command = std::regex_replace(command,argumentDeleter,"");
        }

    }
    return arguments;

 }

 void CommandHandler::promptForCommands(){
     string line = "";
     getline(cin,line);
     int commandNumber = stoi(line);
     while(commandNumber > 0){
         getline(cin,line);
         CommandHandler::parser(line);
         commandNumber--;
     }
 }