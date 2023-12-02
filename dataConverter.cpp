//
// Created by highf on 11/26/2023.
//
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
        timeLookup[timeIter->dump()] = counter;
        weatherVec.push_back( std::make_pair(std::stof(tempIter->dump()),timeIter->dump()));
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