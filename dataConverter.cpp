
#include <fstream>
#include "dataConverter.h"
#include <iostream>

dataConverter::dataConverter(string fileName)
{
    std::ifstream f(fileName);
    json data = json::parse(f);

    json timeData = data["hourly"]["time"];
    json tempData = data["hourly"]["temperature_2m"];
    auto tempIter = tempData.begin();
    int counter  = 0;
    for (auto timeIter = timeData.begin(); timeIter < timeData.end(); timeIter++)
    {
        std::string date = timeIter->dump();
        date = date.substr(1,date.size()-2);
        timeLookup[date] = counter;
        weatherVec.push_back( std::make_pair(std::stof(tempIter->dump()),date));
        counter++;
        tempIter++;
    }
}
std::unordered_map<string, int> dataConverter::getTimeMap(){
    return timeLookup;
}

std::vector<std::pair<float,string>> dataConverter::getWeatherVec(){
    return weatherVec;
}