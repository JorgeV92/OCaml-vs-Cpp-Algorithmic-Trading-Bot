#pragma once
#include <iostream>
//->  library for making HTTP requests 
#include <curl/curl.h>
#include<string>
class alpaca {
    public:
    alpaca();
    void buySellOrder();
    void showInformation();

    private:
    //temporary key and secret that user should use
    const char* apiKey;
    const char* apiSecret;
};