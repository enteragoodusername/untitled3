
#ifndef UNTITLED3_FUNCTIONS_H
#define UNTITLED3_FUNCTIONS_H
#include <vector>
#include <string>
#include <unordered_map>
class Functions
{
public:
    static std::vector<std::pair<float,std::string>> getLongestStreak(const std::vector<std::pair<float,std::string>>&, int low, int high);
    static std::vector<std::pair<float, std::string>> bucketSort(std::unordered_map<std::string, int>& weatherMap, const std::vector<std::pair<float,std::string>>& weatherVec);
    static std::vector<std::pair<float, std::string>> monthlyAverage(const std::vector<std::pair<float, std::string>>& sortWeatherMap);
    static std::pair<float, std::string> hottestMonth (std::vector<std::pair<float, std::string>> weatherVec);
    static std::pair<float, std::string> coldestMonth (std::vector<std::pair<float, std::string>> weatherVec);
    static std::pair<float, std::string> hottest (std::vector<std::pair<float, std::string>> weatherVec);
    static std::pair<float, std::string> coldest (std::vector<std::pair<float, std::string>> weatherVec);
    static std::vector<std::pair<float, std::string>> radixSortTempDescending(std::vector<std::pair<float, std::string>> weatherVec );
    static std::vector<std::pair<float, std::string>> bucketSortTempDescending(std::vector<std::pair<float, std::string>> weatherVec );
};


#endif //UNTITLED3_FUNCTIONS_H
