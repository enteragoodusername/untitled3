#include "functions.h"
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
