#pragma once
#include<vector>
#include<iostream>
#include<fstream>
class algo {
    public:
    // Function to calculate the moving average of prices
    void calculateMovingAverage(const std::vector<double>& prices, int shortTerm, int longTerm);
    void crossOverSignal();
    //generates CSV for moving averages
    void movingAveragesCSV(const std::string& smaFile, const std::string& lmaFile);
    private:

    //both SMA and LMA vector hold old prices first
    //idx  0   1    2
    //ex) 6/9 6/10 6/11
    std::vector<double> SMA;
    std::vector<double> LMA;

};