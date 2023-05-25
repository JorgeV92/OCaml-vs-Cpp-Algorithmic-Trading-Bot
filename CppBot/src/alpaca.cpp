#include "alpaca.h"
#include "userInfo.h"
alpaca::alpaca() {
    apiKey = "PKTWT7C6BFGNJUMTNFOX";
    apiSecret = "iGCcDRwgk7MrYaN4lqB1KfkXkj58aIax5ehHIxNj";
}
//Callback function that captures the response data and appending it to the responseData string
size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* response) {
    //std::cout << "content is " << contents << std::endl;
    size_t totalSize = size * nmemb;
    response->append(contents, totalSize);
    std::cout << "totalSize is " << totalSize << std::endl;
    return totalSize;
}

void alpaca::showInformation() {
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
}

void alpaca::buySellOrder() {
    CURL* curl;
    CURLcode res;

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // Set API endpoint URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://paper-api.alpaca.markets/v2/orders");

        // Set headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "APCA-API-KEY-ID: PKTWT7C6BFGNJUMTNFOX");
        headers = curl_slist_append(headers, "APCA-API-SECRET-KEY: iGCcDRwgk7MrYaN4lqB1KfkXkj58aIax5ehHIxNj");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set request data for buying a stock
        std::string orderData = R"({"symbol":"AAPL","qty":1,"side":"buy","type":"market","time_in_force":"gtc"})";

        // Set request data for selling a stock
        // std::string orderData = R"({"symbol":"AAPL","qty":1,"side":"sell","type":"market","time_in_force":"gtc"})";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, orderData.c_str());

        // Perform the request
        std::cout << "order performed" << std::endl;
        res = curl_easy_perform(curl);
        std::cout << "order finished" << std::endl;

        // Check for errors
        if (res != CURLE_OK)
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    // Cleanup cURL
    curl_global_cleanup();
}