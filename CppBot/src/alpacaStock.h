#pragma once
#include<iostream>
#include<fstream>
#include <sstream>//abstraction that represents a sequence of data that can be read from or written to
//->  library for making HTTP requests 
#include <curl/curl.h>
//->JSON parsing library
#include <json/json.h>
#include<string>
class alpacaStock {
    public:
    std::string api_base_url;
    std::string api_account_url;
    std::string orders_url;
    alpacaStock(std::string key, std::string secret);
    void storeAccountInfo();//shows personal stock information 
    void buySellOrder();
    std::string sendGetRequest(const std::string& url);
    void extractData(std::string stockSymbol, std::string startDate,std::string endDate,std::string timeframe, int limit);//Extracting data information based on stock type, start time, end time, timeframe, limit
    void parseJSONData();
    //it can check timestamps, closed prices etc..
    void generateCSV(const std::string& filename);

    std::vector<double> extractClosedPrices();
    std::string getAccountData();
    private:
    //key and secret that user should use
    std::string apiKey;
    std::string apiSecret;

    std::string accountData;
    std::string infoData;
    //to store the realtime information
    std::vector<std::string> realTimeTimeStamp;
    std::vector<double> openingPrices;
    std::vector<double> highestPrices;
    std::vector<double> lowestPrices;
    std::vector<double> closedPrices;
    std::vector<double> volumeOfTrading;
    std::vector<double> numberOfTrades;
    std::vector<double> vwAveragePrices;

};