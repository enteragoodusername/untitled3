#include <iostream>
#include <fstream>
#include "dataConverter.h"
#include <vector>
#include "functions.h"
#include "CommandHandler.h"


int main()
{
    // gives weather json file name to convert it into a map
    dataConverter obj("weather.json");

    //gets the map representation of it, time (string type) is the key and value  (int) is the corresponding position in the vector
    std::unordered_map<string,int> weatherMap = obj.getTimeMap();
    // vector with temp and time string
    std::vector<std::pair<float,string>> weatherVec = obj.getWeatherVec();


    auto vec = Functions::getLongestStreak(weatherVec, 0, 20);
    std::cout << "Longest streak is from " << vec.front().second << " to " << vec.back().second << std::endl;
    return 0;
}