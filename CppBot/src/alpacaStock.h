#pragma once
#include <iostream>
//->  library for making HTTP requests 
#include <curl/curl.h>
#include<string>
class alpacaStock {
    public:
    alpacaStock(std::string key, std::string secret);
    void showInformation();
    void buySellOrder();
    
    

    private:
    //temporary key and secret that user should use
    std::string apiKey;
    std::string apiSecret;
};