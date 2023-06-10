#include"algorithms.h"
// Function to calculate the moving average of prices
//strategy 1

//will be used to determine both SMA and LMA
//closed prices
void algo::calculateMovingAverage(const std::vector<double>& prices, int shortTerm, int longTerm) {

    //6/5 6/6 6/7 6/8 6/9
    //1 2 3 4 5
    //interval 2

    //set the number of elements for the result moving average
    for (int i = 0; i <= prices.size() - shortTerm; i++) {
        double sum = 0.0;
        //iterate from the start to the number of interval
        for (int j = i; j < i + shortTerm; j++) {
            sum += prices[j];
        }
        double average = sum / shortTerm;
        SMA.push_back(average);
    }

    for (int i = 0; i <= prices.size() - longTerm; i++) {
        double sum = 0.0;
        //iterate from the start to the number of interval
        for (int j = i; j < i + longTerm; j++) {
            sum += prices[j];
        }
        double average = sum / longTerm;
        LMA.push_back(average);
    }
}

void algo::crossOverSignal() {
    // Generate crossover signals
    for (int i = 1; i < SMA.size(); i++) {
        //if SMA Prev < LMA Prev && 
        if (SMA[i] > LMA[i] && SMA[i - 1] < LMA[i - 1]) {
            std::cout << "Buy signal at index " << i << std::endl;
        } else if (SMA[i] < LMA[i] && SMA[i - 1] > LMA[i - 1]) {
            std::cout << "Sell signal at index " << i << std::endl;
        } else {
            std::cout << "No crossover signal at index " << i << std::endl;
        }
    }
}

//generates CSV for moving averages
void algo::movingAveragesCSV(const std::string& smaFile, const std::string& lmaFile) {
    std::ofstream file(smaFile);//output stream for writing to files
    if(file.is_open()) {
        file << "SMA" << std::endl;
        for(size_t i = 0; i < SMA.size(); i++) {
            file << SMA[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to open the SMA file to put the data." << std::endl;
    }

    std::ofstream file2(lmaFile);//output stream for writing to files
    if(file2.is_open()) {
        file2 << "LMA" << std::endl;
        for(size_t i = 0; i < LMA.size(); i++) {
            file2 << LMA[i] << std::endl;
        }
        file2.close();
    } else {
        std::cerr << "Failed to open the LMA file to put the data." << std::endl;
    }

    return;
}
