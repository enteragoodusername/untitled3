
#ifndef UNTITLED3_FUNCTIONS_H
#define UNTITLED3_FUNCTIONS_H
#include <vector>
#include <string>
#include <unordered_map>
class Functions
{
public:
    static std::vector<std::pair<float,std::string>> getLongestStreak(const std::vector<std::pair<float,std::string>>&, float low, float high);
    static std::vector<std::pair<float, std::string>> bucketSort(std::unordered_map<std::string, int>& weatherMap, const std::vector<std::pair<float,std::string>>& weatherVec);
    static std::vector<std::pair<float, std::string>> monthlyAverage(const std::vector<std::pair<float, std::string>>& sortWeatherMap);
    static std::pair<float, std::string> hottest (std::vector<std::pair<float, std::string>> weatherVec);
    static std::pair<float, std::string> coldest (std::vector<std::pair<float, std::string>> weatherVec);
    static std::vector<std::pair<float, std::string>> radixSortTempDescending(std::vector<std::pair<float, std::string>> weatherVec );
    static std::vector<std::pair<float, std::string>> bucketSortTempDescending(std::vector<std::pair<float, std::string>> weatherVec );
    static std::vector<std::pair<float, std::string>> dailyAverage(const std::vector<std::pair<float, std::string>>& sortWeatherMap);
    static std::vector<std::pair<float, std::string>> yearlyAverage(const std::vector<std::pair<float, std::string>>& sortWeatherMap);
};


#endif //UNTITLED3_FUNCTIONS_H
