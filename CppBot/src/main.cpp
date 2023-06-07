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
  

  return 0;
}