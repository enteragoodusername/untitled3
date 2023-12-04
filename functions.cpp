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

std::vector<std::pair<float, std::string>> Functions::monthlyAverage(const std::vector<std::pair<float, std::string>>& sortWeatherMap) {

    std::vector<std::pair<float, std::string>> averages;

    std::string monthStr = sortWeatherMap.front().second.substr(5,2);
    std::string yearStr = sortWeatherMap.front().second.substr(0,4);
    

    int counter = 0;
    float monthSum = 0;

   for(auto iter = sortWeatherMap.begin(); iter != sortWeatherMap.end(); iter++){
       if (iter->second.substr(5,2) == monthStr){
           monthSum += iter->first;
           counter++;
       }
       else{
           averages.push_back(std::make_pair(monthSum/counter,yearStr +"-"+monthStr));
           monthStr = iter->second.substr(5,2);
           yearStr = iter->second.substr(0,4);
           counter = 0;
           monthSum = 0;
       }
   };

    return averages;

}

std::pair<float, std::string> Functions::hottestMonth (std::vector<std::pair<float, std::string>> weatherVec){
    auto averages = monthlyAverage(weatherVec);
    return hottest(averages);
}
std::pair<float, std::string> Functions::coldestMonth (std::vector<std::pair<float, std::string>> weatherVec){
    return coldest(monthlyAverage(weatherVec));
}

std::pair<float, std::string> Functions::coldest(std::vector<std::pair<float, std::string>> weatherVec){
    std::vector<std::pair<float, std::string>> averages = monthlyAverage(weatherVec);
    std::pair<float,std::string> coldest = weatherVec.front();
    for(auto& pair: weatherVec){
        if (pair.first < coldest.first){
            coldest = pair;
        }
    }
    return coldest;
}
std::pair<float, std::string> Functions::hottest(std::vector<std::pair<float, std::string>> weatherVec){
    std::vector<std::pair<float, std::string>> averages = monthlyAverage(weatherVec);
    std::pair<float,std::string> hottest = weatherVec.front();
    for(auto& pair: weatherVec){
        if (pair.first > hottest.first){
            hottest = pair;
        }
    }
    return hottest;
}

std::vector<std::pair<float, std::string>> Functions::radixSortTempDescending(std::vector<std::pair<float, std::string>> weatherVec ) {
    const int numBuckets = 200; // Number of buckets for counting sort (-50 to 150 range)

    // Function to perform counting sort on the given digit (exp)
    auto countingSort = [&](const std::vector<std::pair<float, std::string>>& input, size_t exp) -> std::vector<std::pair<float, std::string>> {
        std::vector<std::pair<float, std::string>> result;
        std::vector<std::vector<std::pair<float, std::string>>> buckets(numBuckets);

        // Distribute elements into buckets
        for (const auto& pair : input) {
            int bucketIndex = static_cast<int>((pair.first + 50.0f) * 10) / exp % numBuckets;
            buckets[bucketIndex].emplace_back(pair);
        }

        // Collect elements from buckets in reverse order
        for (auto it = buckets.rbegin(); it != buckets.rend(); ++it) {
            result.insert(result.end(), it->begin(), it->end());
        }

        return result;
    };

    // Convert the unordered_map to a vector of pairs
    std::vector<std::pair<float, std::string>> inputVector;

    for (auto it = weatherVec.begin(); it != weatherVec.end(); ++it) {
        inputVector.emplace_back(it->first, it->second);
    }

    // Apply counting sort to sort elements based on individual digits
    for (size_t exp = 1; exp < 1000; exp *= 10) {
        inputVector = countingSort(inputVector, exp);
    }

    return inputVector;
}

void insertionSortTemp(std::vector<std::pair<float, std::string>>& bucket) {
    for (int i = 1; i < bucket.size(); ++i) {
        auto key = bucket[i];
        int j = i - 1;

        // Compare temperatures for sorting (in descending order)
        while (j >= 0 && bucket[j].first > key.first) {
            bucket[j + 1] = bucket[j];
            --j;
        }
        bucket[j + 1] = key;
    }
}

std::vector<std::pair<float, std::string>> Functions::bucketSortTempDescending(std::vector<std::pair<float, std::string>> weatherVec ) {
    const int numBuckets = 201;  // Buckets for temperatures from -50 to 150

    // Create buckets
    std::vector<std::vector<std::pair<float, std::string>>> buckets(numBuckets);

    // Distribute elements into buckets based on the temperature
    for (const auto& entry : weatherVec) {
        // Ensure temperature is within the desired range
        float temperature = std::max(-50.0f, std::min(150.0f, entry.first));

        // Map temperature to bucket index
        int bucketIndex = static_cast<int>(temperature + 50.0);
        //std::cout << bucketIndex << std::endl;
        // Add entry to the corresponding bucket
        buckets[bucketIndex].emplace_back(entry);
    }

    // Clear the original map
    //weatherMap.clear();

    std::vector<std::pair<float, std::string>> sortedData;
    // Concatenate buckets back into the map in sorted order
    for (auto it = buckets.rbegin(); it != buckets.rend(); ++it) {
        insertionSortTemp(*it);
        for (auto entryIt = it->rbegin(); entryIt != it->rend(); ++entryIt) {
            sortedData.emplace_back(entryIt->first, entryIt->second);
        }
    }

    return sortedData;
}