#include <iostream>
#include <fstream>
#include "dataConverter.h"


int main()
{
    // gives weather json file name to convert it into a map
    dataConverter obj("weather.json");

    //gets the map representation of it, time (string type) is the key and temperature (float) is the value
    std::unordered_map<string,float> weatherMap = obj.getTimeMap();

    // outputs times and temperature. Note that because map is unordered it wont order by time
    for(auto iter = weatherMap.begin(); iter != weatherMap.end(); iter++){
        std::cout << "Time: "<<iter->first << " Temp (C): " << iter->second << std::endl;
    }
    return 0;
}
