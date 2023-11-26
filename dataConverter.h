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
    std::unordered_map<string, float> getTimeMap();

private:
    std::unordered_map<string, float> timeLookup;
    std::vector<int> weatherVec;

};


#endif //UNTITLED3_DATACONVERTER_H
