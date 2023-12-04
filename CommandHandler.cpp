// Note: this comes from a group members project 1 code
#include <regex>
#include "CommandHandler.h"
#include <iostream>
#include <sstream>
#include "functions.h"
#include "dataConverter.h"

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
     std::cout << "Predicting Weather for Brighter Futures" << std::endl;
     std::cout << "This program has hourly temperature data from 2000-01-01 to 2023-12-2\n\n"<< std::endl;
     while(true){
         std::cout <<  "1.  Highest Temp "<< std::endl;
         std::cout << "2.  Coldest Temp "<< std::endl;
         std::cout << "3.  Longest Temp "<< std::endl;
         std::cout << "4.  Hottest Month "<< std::endl;
         std::cout << "5.  Coldest Month "<< std::endl;
         std::cout << "Enter Option:"<< std::endl;
         getline(cin,line);
         if (line == ""){
             return;
         }
         CommandHandler::parser(line);
     }
 }