#include <iostream>
//->  library for making HTTP requests 
#include <curl/curl.h>
#include"userInfo.h"

//Callback function that captures the response data and appending it to the responseData string
size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* response) {
    //std::cout << "content is " << contents << std::endl;
    size_t totalSize = size * nmemb;
    response->append(contents, totalSize);
    std::cout << "totalSize is " << totalSize << std::endl;
    return totalSize;
}

int main() {
  //cUrl initialization -> set various options and perform HTTP requests with cURL.
  CURL* curl = curl_easy_init();
  if (curl) {
    // Set the API endpoint URL
    const char* url = "https://paper-api.alpaca.markets/v2/account";
    
    // Set up personal Alpaca API key and secret
    const char* apiKey = "PKTWT7C6BFGNJUMTNFOX";
    const char* apiSecret = "iGCcDRwgk7MrYaN4lqB1KfkXkj58aIax5ehHIxNj";

    // Set the request headers
    struct curl_slist* headers = NULL;
    std::string strAPIKey = "APCA-API-KEY-ID: " + std::string(apiKey);
    headers = curl_slist_append(headers, strAPIKey.c_str());
    std::string strAPISecret = "APCA-API-SECRET-KEY: " + std::string(apiSecret);
    headers = curl_slist_append(headers, strAPISecret.c_str());

  
    // Create a string to store the response data
    std::string responseData;

    // Set cURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

 
    // Perform the request
    CURLcode res = curl_easy_perform(curl);


    
    
    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    } else {
      // Print the response data
      std::cout << "Response data: " << responseData << std::endl;
      std::cout << "\n";
      std::cout << "\n";
      userInformation UI(responseData);

    }


    // Cleanup the things
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    std::cout << "successfully working" << std::endl;
  }

  return 0;
}