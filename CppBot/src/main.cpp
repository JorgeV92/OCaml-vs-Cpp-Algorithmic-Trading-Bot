#include"alpacaStock.h"
#include"userInfo.h"
#include"algorithms.h"
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
  //A.crossOverSignal();
  A.movingAveragesCSV("SMA.csv", "LMA.csv");
  

  return 0;
}