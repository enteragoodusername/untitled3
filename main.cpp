#include <iostream>
#include <fstream>
#include "dataConverter.h"
#include <vector>


int main()
{
    // gives weather json file name to convert it into a map
    dataConverter obj("weather.json");

    //gets the map representation of it, time (string type) is the key and value  (int) is the corresponding position in the vector
    std::unordered_map<string,int> weatherMap = obj.getTimeMap();
    // vector with temp and time string
    std::vector<std::pair<float,string>> weatherVec = obj.getWeatherVec();

    for (auto& pair :weatherVec){
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    return 0;
}