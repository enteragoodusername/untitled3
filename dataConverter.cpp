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
    for (auto timeIter = timeData.begin(); timeIter < timeData.end(); timeIter++)
    {
        timeLookup[timeIter->dump()] = std::stof(tempIter->dump());
        tempIter++;
    }
}
std::unordered_map<string, float> dataConverter::getTimeMap(){
    return timeLookup;
}