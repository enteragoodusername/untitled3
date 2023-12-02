//
// Created by highf on 11/26/2023.
//

#ifndef UNTITLED3_DATACONVERTER_H
#define UNTITLED3_DATACONVERTER_H
#include "json.hpp"
#include <string>
#include <unordered_map>
#include <vector>

using nlohmann::json;
using std::string;
class dataConverter
{
public:
    dataConverter(string fileName);
    std::unordered_map<string, int> getTimeMap();
    std::vector<std::pair<float,string>> getWeatherVec();
private:
    std::unordered_map<string, int> timeLookup;
    std::vector<std::pair<float,string>> weatherVec;

};


#endif //UNTITLED3_DATACONVERTER_H
