#include <iostream>
//->  library for making HTTP requests 
#include <curl/curl.h>

int main() {
  //cUrl initialization -> set various options and perform HTTP requests with cURL.
  CURL* curl = curl_easy_init();
  if (curl) {
    // Set the API endpoint URL
    const char* url = "https://paper-api.alpaca.markets/v2/account";
    
    // Set up your personal Alpaca API key and secret
    const char* apiKey = "PKTWT7C6BFGNJUMTNFOX";
    const char* apiSecret = "iGCcDRwgk7MrYaN4lqB1KfkXkj58aIax5ehHIxNj";

    // Set the request headers
    struct curl_slist* headers = NULL;
    std::string strAPIKey = "APCA-API-KEY-ID: " + std::string(apiKey);
    headers = curl_slist_append(headers, strAPIKey.c_str());
    std::string strAPISecret = "APCA-API-SECRET-KEY: " + std::string(apiSecret);
    headers = curl_slist_append(headers, strAPISecret.c_str());

 
    // Set cURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    
    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Cleanup the things
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    std::cout << "successfully working" << std::endl;
  }

  return 0;
}