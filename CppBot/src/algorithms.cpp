#include<algorithms.h>
// Function to calculate the moving average of prices
//strategy 1
std::vector<double> algo::calculateMovingAverage(const std::vector<double>& prices, int windowSize) {
    std::vector<double> movingAverages;

    for (int i = 0; i <= prices.size() - windowSize; i++) {
        double sum = 0.0;
        for (int j = i; j < i + windowSize; j++) {
            sum += prices[j];
        }
        double average = sum / windowSize;
        movingAverages.push_back(average);
    }

    return movingAverages;
}
