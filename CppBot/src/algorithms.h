#pragma once
#include<vector>

class algo {
    public:
    // Function to calculate the moving average of prices
    double calculateMovingAverage(const std::vector<double>& prices) {
        double sum = 0.0;
        for (const auto& price : prices) {
            sum += price;
        }
        return sum / prices.size();
    }

    private:

};