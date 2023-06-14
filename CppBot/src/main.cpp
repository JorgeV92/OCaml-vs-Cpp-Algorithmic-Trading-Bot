#include"alpacaStock.h"
#include"userInfo.h"
#include"algorithms.h"
#include"test.cpp"
int main() {
  std::string key;
  std::string secret;
  std::cout << "put your alpaca key: " << std::endl;
  std::cin >> key;
  std::cout << "put your alpaca secret: " << std::endl;
  std::cin >> secret;
  alpacaStock ap = alpacaStock(key, secret);
  //ap.buySellOrder();
  //ap.showInformation();
  ap.extractRealtimeInfo();

  //closed prices stores an old prices first
  const std::vector<double> closedPrices = ap.extractClosedPrices();
  for(size_t i = 0; i < closedPrices.size(); i++) {
    std::cout << "price is " << closedPrices[i] << std::endl;
  }

  algo A;
  A.calculateMovingAverage(closedPrices, 10, 20);
  A.crossOverSignal();
  A.movingAveragesCSV("SMA.csv", "LMA.csv");
  
  //std::cout << "size of closedPrices " << closedPrices.size() << std::endl;
  // double sma = 0.0;
  //   for(size_t i = 0; i < 10; i++) {
  //       sma+= closedPrices[i];
  //   }
  //   sma /= 10.0;

  // std::cout << "sma first elem is " << sma << std::endl;

  // double lma = 0.0;
  //   for(size_t i = 0; i < 20; i++) {
  //       lma+= closedPrices[i];
  //   }
  //   lma /= 20.0;
  // std::cout << "LMA first elem is " << lma << std::endl;

  
  return 0;
}