#pragma once
#include <iostream>
//->  library for making HTTP requests 
#include <curl/curl.h>
#include<string>
class alpacaStock {
    public:
    std::string api_base_url;
    std::string api_account_url;
    std::string orders_url;
    alpacaStock(std::string key, std::string secret);
    void showInformation();
    void buySellOrder();

    // Struct for storing API response data
    struct responseData {
        std::string response;
        long http_code;
    };
    responseData sendGetRequest(const std::string& url);
    

    private:
    //temporary key and secret that user should use
    std::string apiKey;
    std::string apiSecret;

    


};