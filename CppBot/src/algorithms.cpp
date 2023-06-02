#include<algorithms.h>
// Function to calculate the moving average of prices
//strategy 1
double algo::calculateMovingAverage(const std::vector<double>& prices) {
    double sum = 0.0;
    // for (const auto& price : prices) {
    //     sum += price;
    // }
    for(size_t i = 0; i < prices.size(); i++) {
        sum += prices[i];
    }
    return (sum / prices.size());
}
