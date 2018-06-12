//
// Created by Brian Swenson on 2/8/18.
//

#ifndef E2_E2_H
#define E2_E2_H

#include <vector>
#include <future>

long vectorSum(const std::vector<int>& vec, int& minVal, int& maxVal, int& one_eight) {
    long one_sum=0L;
    for(int i = 0; i < one_eight; ++i) {
        one_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return one_sum;
}

long vectorSum2(const std::vector<int>& vec, int& minVal, int& maxVal, int& one_eight, int& two_eight) {
    long two_sum = 0L;
    for(int i = one_eight; i < two_eight; ++i) {
        two_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return two_sum;
}

long vectorSum3(const std::vector<int>& vec, int& minVal, int& maxVal, int& two_eight, int& three_eight) {
    long three_sum = 0L;
    for(int i = two_eight; i < three_eight; ++i) {
        three_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return three_sum;
}

long vectorSum4(const std::vector<int>& vec, int& minVal, int& maxVal, int& three_eight, int& four_eight) {
    long four_sum = 0L;
    for(int i = three_eight; i < four_eight; ++i) {
        four_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return four_sum;
}

long vectorSum5(const std::vector<int>& vec, int& minVal, int& maxVal, int& four_eight, int& five_eight) {
    long five_sum = 0L;
    for(int i = four_eight; i < five_eight; ++i) {
        five_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return five_sum;
}

long vectorSum6(const std::vector<int>& vec, int& minVal, int& maxVal, int& five_eight, int& six_eight) {
    long six_sum = 0L;
    for(int i = five_eight; i < six_eight; ++i) {
        six_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return six_sum;
}

long vectorSum7(const std::vector<int>& vec, int& minVal, int& maxVal, int& six_eight, int& seven_eight) {
    long seven_sum = 0L;
    for(int i = six_eight; i < seven_eight; ++i) {
        seven_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return seven_sum;
}

long vectorSum8(const std::vector<int>& vec, int& minVal, int& maxVal, int& seven_eight, int& eight) {
    long eight_sum = 0L;
    for(int i = seven_eight; i < eight; ++i) {
        eight_sum += vec[i];
        if(vec[i] < minVal) minVal = vec[i];
        if(vec[i] > maxVal) maxVal = vec[i];
    }
    return eight_sum;
}

#endif //E2_E2_H
