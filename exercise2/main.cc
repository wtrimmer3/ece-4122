#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "e2.h"

// William Trimmer
namespace sc = std::chrono;

int main() {

    std::vector<int> myVec (50000000);
    std::srand(0);

    //another, better option would be to use std::generate and a c++11ish random generator
    for(int i = 0; i < myVec.capacity(); ++i) {
        myVec[i] = std::rand() % 1000;
    }

    //http://en.cppreference.com/w/cpp/chrono
    auto start = sc::high_resolution_clock::now();

    int minVal;
    int maxVal;
    long sum;
    double average;

    /* WITHOUT THREADS
    for(auto& i: myVec) {
        sum += i;
        if(i < minVal) minVal = i;
        if(i > maxVal) maxVal = i;
    }
    average = sum/double(myVec.size());
    */

    // WITH THREADS
    int one_eight = myVec.size()/8;
    int two_eight = myVec.size()/4;
    int three_eight = 3*myVec.size()/8;
    int four_eight = myVec.size()/2;
    int five_eight = 5*myVec.size()/8;
    int six_eight = 3*myVec.size()/4;
    int seven_eight = 7*myVec.size()/8;
    int eight = myVec.size();
    std::future<long> f1 = std::async(std::launch::async, [&] {return vectorSum(myVec, minVal, maxVal, one_eight);});
    std::future<long> f2 = std::async(std::launch::async, [&] {return vectorSum2(myVec, minVal, maxVal, one_eight, two_eight);});
    std::future<long> f3 = std::async(std::launch::async, [&] {return vectorSum3(myVec, minVal, maxVal, two_eight, three_eight);});
    std::future<long> f4 = std::async(std::launch::async, [&] {return vectorSum4(myVec, minVal, maxVal, three_eight, four_eight);});
    std::future<long> f5 = std::async(std::launch::async, [&] {return vectorSum5(myVec, minVal, maxVal, four_eight, five_eight);});
    std::future<long> f6 = std::async(std::launch::async, [&] {return vectorSum6(myVec, minVal, maxVal, five_eight, six_eight);});
    std::future<long> f7 = std::async(std::launch::async, [&] {return vectorSum7(myVec, minVal, maxVal, six_eight, seven_eight);});
    std::future<long> f8 = std::async(std::launch::async, [&] {return vectorSum8(myVec, minVal, maxVal, seven_eight, eight);});
    sum = f1.get() + f2.get() + f3.get() + f4.get() + f5.get() + f6.get() + f7.get() + f8.get();
    average = double(sum/double(myVec.size()));


    //todo:  insert code here to populate these values
    //       the final execution time must be faster
    //       than what can be achieved with a single thread
    //      bonus points will be rewarded for fastest times

    auto end = sc::high_resolution_clock::now();

    std::cout << "Min: " << minVal << std::endl;
    std::cout << "Max: " << maxVal << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;

    std::cout << "Elapsed Time: " << sc::duration_cast<sc::milliseconds>(end - start).count() << "ms" << std::endl;
}