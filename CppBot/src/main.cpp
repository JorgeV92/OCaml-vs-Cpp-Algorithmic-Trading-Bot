#include"alpacaStock.h"
#include"userInfo.h"
#include"algorithms.h"
#include <iomanip>
#include <openssl/sha.h>
int main() {
  //Getting information from the user for certification to alpaca api
  std::string key;
  std::string secret;
  std::cout << "put your alpaca key: " << std::endl;
  std::cin >> key;
  std::cout << "put your alpaca secret: " << std::endl;
  std::cin >> secret;
  alpacaStock ap = alpacaStock(key, secret);

  ap.storeAccountInfo();
  std::string accountData = ap.getAccountData();
  userInformation ui(accountData, key, secret); 
  ui.makeUserDB();
  //1. hashing
  //2. make the bot to order the stuff
  //3. check the current amount of money that user has and count the how many stock user can buy



  // //ap.buySellOrder();
  // //ap.showInformation();

  // //Provide stock information for the desired time period requested by the user.
  std::string stockSymbol;
  std::string startDate;
  std::string endDate;
  std::string timeframe;
  int limit;
  // Ask user for input
  std::cout << "Enter the stock symbol: ";
  std::cin >> stockSymbol;

  std::cout << "Enter the start date |YYYY-MM-DD|: ";
  std::cin >> startDate;

std::cout << "End date should always be filled with yesterday's date";
  std::cout << "Enter the end date |YYYY-MM-DD|: ";
  std::cin >> endDate;

  std::cout << "Enter the timeframe (1Min, 1Hour, 1Day): ";
  std::cin >> timeframe;

  std::cout << "Enter the limit (number): ";
  std::cin >> limit;


  ap.extractData(stockSymbol, startDate, endDate,timeframe, limit);
  ap.parseJSONData();


  
  //closed prices stores an old prices first
  const std::vector<double> closedPrices = ap.extractClosedPrices();
  std::cout << "closedprices size is " << closedPrices.size() << std::endl;
  for(size_t i = 0; i < closedPrices.size(); i++) {
    std::cout << "price is " << closedPrices[i] << std::endl;
  }
  algo A;
  
  A.calculateMovingAverage(closedPrices, 10, 20);
  A.crossOverSignal();
  //should ask user the qty for the stock to either buy or sell the stock
  std::string finalBotSignal = A.getFinalSignalForBotToTrade();
  if(finalBotSignal == "hold") {
    std::cout << "since finalBotSignal is hold, we don't need any action for bot to run!" << std::endl;
    exit(0);
  }
  int qty;
  //we have to check the qty by getting current currency that user has and calculate the stockmoney to either buy or sell
  std::cout << "Enter the quantity you want this bot to " + finalBotSignal +" this " +  "stock: " + stockSymbol + "(number): ";
  std::cin >> qty;
  ap.buySellOrder(stockSymbol, qty, finalBotSignal);
  A.movingAveragesCSV("SMA.csv", "LMA.csv");
  
  // std::cout << "size of closedPrices " << closedPrices.size() << std::endl;
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