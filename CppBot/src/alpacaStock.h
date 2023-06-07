#pragma once
#include<iostream>
#include<fstream>
//->  library for making HTTP requests 
#include <curl/curl.h>
//->JSON parsing library
#include <json/json.h>
#include<string>


template<typename T>
void generateCSV(const std::vector<T>& dataVect, const std::string& filename);

class alpacaStock {
    public:
    std::string api_base_url;
    std::string api_account_url;
    std::string orders_url;
    alpacaStock(std::string key, std::string secret);
    void showInformation();//shows personal stock information 
    void buySellOrder();
    std::string sendGetRequest(const std::string& url);
    void extractRealtimeInfo();//extract realtime information for specific stock option -> can check timestamps, closed prices etc..
    // void generateTimestampCSV(const std::vector<T>& dataVect, const std::string& filename);

    private:
    //temporary key and secret that user should use
    std::string apiKey;
    std::string apiSecret;

    //to store the realtime information
    std::vector<std::string> realTimeTimeStamp;
    std::vector<double> closedPrices;

    


};