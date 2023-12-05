// Note:A part of this comes from a group members project 1 code
#include <regex>
#include "CommandHandler.h"
#include <iostream>
#include <sstream>
#include "functions.h"
#include "dataConverter.h"
#include <chrono>

using std::string;
using std::cout;
using std::cin;

std::vector<std::pair<float,std::string>> currentWeatherVec;
std::unordered_map<std::string, int> dateLookup;
std::vector<std::pair<float,std::string>> weatherVec;
std::string scope = "hourly";

// parses command line in order to choose proper command, also verifies that id and name have appropriate syntax
 void CommandHandler::parser(string command) {
     std::vector<string> arguments = CommandHandler::parseArguments(command);
     if (arguments.size() == 1){
         if (arguments[0] == "1"){
             std::cout << "Input start date in yyyy-mm-dd format:" << std::endl;
             string input = "";
             getline(cin,input);
             input += "T00:00";\
             int start = dateLookup[input];

             std::cout << "Input end date in yyyy-mm-dd format:" << std::endl;
             input = "";
             getline(cin,input);
             input += "T00:00";\
             int end = dateLookup[input];
             currentWeatherVec.clear();
             for (int i = start; i < end +1;i++){
                 currentWeatherVec.push_back(weatherVec[i]);
             }
             std::cout <<  "Select Scope"<< std::endl;
             std::cout <<  "1. Hourly"<< std::endl;
             std::cout <<  "2. Daily"<< std::endl;
             std::cout <<  "3. Monthly"<< std::endl;
             std::cout <<  "4. Yearly"<< std::endl;

              input = "";
             getline(cin,input);

             if (input == "1"){
                 scope = "hourly";
             }
             else if(input == "2") {
                 scope = "daily";
                 currentWeatherVec = Functions::dailyAverage(currentWeatherVec);
             }
             else if (input == "3"){
                 scope = "Monthly";
                 currentWeatherVec = Functions::monthlyAverage(currentWeatherVec);

             }
             else if(input == "4") {
                 scope = "Yearly";
                 currentWeatherVec = Functions::yearlyAverage(currentWeatherVec);
             }
             cout << "Scope and time period changed" << std::endl;


         }
         else if (arguments[0] == "2"){
             std::chrono::time_point<std::chrono::steady_clock> time;
             // note that code was taken from a group members treemap vs hashmap assigment;
             auto timeBefore = std::chrono::steady_clock::now();
             auto out = Functions::radixSortTempDescending(currentWeatherVec);
             auto timeAfter = std::chrono::steady_clock::now();
             long long timeElapsed = (std::chrono::duration_cast<std::chrono::nanoseconds>(timeAfter-timeBefore)).count();
             /*
             for (auto& pair : out){
                 cout << pair.second << " : " << pair.first << std::endl;
             }
              */

              cout << "Time for radix sort: "<<timeElapsed / 1000000.0 << " ms" << std::endl;
          }
          else if (arguments[0] == "3"){
              std::chrono::time_point<std::chrono::steady_clock> time;
              // note that code was taken from a group members treemap vs hashmap assigment;
              auto timeBefore = std::chrono::steady_clock::now();
              auto out = Functions::bucketSortTempDescending(currentWeatherVec);
              auto timeAfter = std::chrono::steady_clock::now();
              long long timeElapsed = (std::chrono::duration_cast<std::chrono::nanoseconds>(timeAfter-timeBefore)).count();
             /*
             for (auto& pair : out){
                 cout << pair.second << " : " << pair.first << std::endl;
             }
              */

             cout << "Time for bucket sort: "<<timeElapsed / 1000000.0 << " ms" << std::endl;
         }
         else if (arguments[0] == "4"){
             std::pair<float,string> pair = Functions::hottest(currentWeatherVec);
             cout << "Hottest datapoint: " << pair.second <<" : "<< pair.first <<std::endl;
         }
         else if (arguments[0] == "5"){
             std::pair<float,string> pair = Functions::coldest(currentWeatherVec);
             cout << "Coldest datapoint: " << pair.second <<"  "<< pair.first <<std::endl;
         }
         else if (arguments[0] == "6"){
             string input1 = "";
             cout << "Input first temperature: " << std::endl;
             getline(cin,input1);
             string input2 = "";
             cout << "Input second temperature: " << std::endl;
             getline(cin,input2);


             std::vector<std::pair<float,std::string>> streak = Functions::getLongestStreak(currentWeatherVec, stof(input1),stof(input2));
             if (streak.size() == 0)
             {
                 cout << "No datapoints fit the criteria" << std::endl;
             }
             else{
                     cout << "Longest streak from " << streak.front().second << " to " << streak.back().second
                          << std::endl;
                     cout << "Total length in datapoints " << streak.size() << std::endl;
                 }


         }
         string unused = "";
         cout << "\nPress enter to return to menu" << std::endl;
         getline(cin,unused);

     }
     else{
         std::cout << "Command not recognized! Please input valid command number.";
     }

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
     std::cout << "Loading...\n\n" << std::endl;
     dataConverter data =dataConverter("weather.json");
     std::cout << "Weather for Brighter Futures" << std::endl;
     std::cout << "This program has hourly temperature data from 2000-01-01 to 2023-11-28 at the University of Florida"<< std::endl;

     dateLookup = data.getTimeMap();
     weatherVec = data.getWeatherVec();

     currentWeatherVec = weatherVec;



     while(true){
         std::cout << "\nCurrent time range: " << currentWeatherVec.front().second <<  " to " << currentWeatherVec.back().second  << std::endl;
         cout << "Current Scope: " << scope << std::endl;
         std::cout << "# of data points: "<<currentWeatherVec.size() << std::endl;
         std::cout <<  "1.  Select Range "<< std::endl;
         std::cout <<  "2.  Radix sort"<< std::endl;
         std::cout << "3.  Bucket Sort "<< std::endl;
         std::cout << "4.  Hottest Datapoint "<< std::endl;
         std::cout << "5.  Coldest Datapoint "<< std::endl;
         std::cout << "6.  Longest Streak Between Temperatures "<< std::endl;
         std::cout << "Enter Option:"<< std::endl;
         getline(cin,line);
         if (line == ""){
             return;
         }
         CommandHandler::parser(line);
     }
 }