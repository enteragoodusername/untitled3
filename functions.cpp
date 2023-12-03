#include "functions.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
std::vector<std::pair<float,std::string>> Functions::getLongestStreak(const std::vector<std::pair<float,std::string>>& weatherVec, int low, int high){
    int longestIndex = -1;
    int longestChain = 0;
    int currentIndex = -1;
    int currentChain = 0;
    bool onChain = false;

    for (int i = 0; i < weatherVec.size(); i++){
        if ( low <= weatherVec[i].first && weatherVec[i].first <= high){
            if (!onChain){
                onChain = true;
                currentIndex = i;
                currentChain = 0;
            }
            currentChain++;
        }
        else{
            if (onChain){
                onChain = false;
                if (currentChain > longestChain){
                    longestIndex = currentIndex;
                    longestChain = currentChain;
                }
            }

        }
    }
    if (onChain){
        onChain = false;
        if (currentChain > longestChain){
            longestIndex = currentIndex;
            longestChain = currentChain;
        }
    }
    std::vector<std::pair<float,std::string>> returnVec;
    if (currentIndex != -1){
        for(int i = longestIndex; i < longestIndex +longestChain; i++){
            returnVec.push_back(weatherVec[i]);
        }
    }
    return returnVec;
}

void insertionSort(std::vector<std::pair<std::string, float>>& bucket) {
    for (int i = 1; i < bucket.size(); ++i) {
        auto key = bucket[i];
        int j = i - 1;
        //std::cout << bucket[i].first << std::endl;
        // Compare minutes for sorting
        while (j >= 0 && (bucket[j].first.substr(11, 2) > key.first.substr(11, 2))) {
            bucket[j + 1] = bucket[j];
            --j;
        }
        bucket[j + 1] = key;
    }
}

std::vector<std::pair<float, std::string>> Functions::bucketSort(std::unordered_map<std::string, int>& weatherMap, const std::vector<std::pair<float,std::string>>& weatherVec) {
    const int numYearBuckets = 24;  // 24 years to choose from
    const int numMonthBuckets = 12;  // 12 months to choose from
    const int numDayBuckets = 31;  // 31 days to choose from
    const int numHourBuckets = 24;  // 24 hours to choose from

    // Create buckets
    std::vector<std::vector<std::vector<std::vector<std::pair<std::string, float>>>>> buckets(numYearBuckets,
            std::vector<std::vector<std::vector<std::pair<std::string, float>>>>(numMonthBuckets,
                    std::vector<std::vector<std::pair<std::string, float>>>(numDayBuckets)));

    // Distribute elements into buckets based on the year, month, day, and hour
    for (const auto& entry : weatherMap) {
        int year = std::stoi(entry.first.substr(2, 2)) % numYearBuckets;
        int month = std::stoi(entry.first.substr(5, 2)) - 1;
        int day = std::stoi(entry.first.substr(8, 2)) - 1;
        int hour = std::stoi(entry.first.substr(11, 2));

        buckets[year][month][day].emplace_back(entry);

    }

    // Clear the original map
    weatherMap.clear();

    // Sort each bucket using insertion sort
    std::vector<std::pair<float, std::string>> sortedData;
    for (auto& yearBucket : buckets) {
        for (auto& monthBucket : yearBucket) {
            for (auto& dayBucket : monthBucket) {
                //for (auto& hourBucket : dayBucket) {
                insertionSort(dayBucket);
                for (const auto& entry : dayBucket) {
                    sortedData.emplace_back(weatherVec[entry.second].first, entry.first);

                }
                // }
            }
        }
    }

    return sortedData;
}