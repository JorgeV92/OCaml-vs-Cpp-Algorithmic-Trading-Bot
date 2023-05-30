#include "alpacaStock.h"
#include "userInfo.h"
//constructor
alpacaStock::alpacaStock(std::string key, std::string secret) {
    apiKey = key;
    apiSecret = secret;
    //paper api right now
    api_base_url = "https://paper-api.alpaca.markets";
    api_account_url = api_base_url + "/v2/account";
    orders_url = api_base_url + "/v2/orders";

}

//Callback function that captures the response data and appending it to the responseData string
size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* response) {
    //std::cout << "content is " << contents << std::endl;
    size_t totalSize = size * nmemb;
    response->append(contents, totalSize);
    std::cout << "totalSize is " << totalSize << std::endl;
    return totalSize;
}

void alpacaStock::showInformation() {
    //cUrl initialization -> set various options and perform HTTP requests with cURL.
  CURL* curl = curl_easy_init();
  if (curl) {
    // Set the API endpoint URL
    const char* url = "https://paper-api.alpaca.markets/v2/account";

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

void alpacaStock::buySellOrder() {
    CURL* curl;
    CURLcode res;

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // Set API endpoint URL
        //paper-api for the fake money
        curl_easy_setopt(curl, CURLOPT_URL, "https://paper-api.alpaca.markets/v2/orders");

        // Set headers
        struct curl_slist* headers = NULL;
        std::string strAPIKey = "APCA-API-KEY-ID: " + std::string(apiKey);
        headers = curl_slist_append(headers, strAPIKey.c_str());
        std::string strAPISecret = "APCA-API-SECRET-KEY: " + std::string(apiSecret);
        headers = curl_slist_append(headers, strAPISecret.c_str());
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


//GET REQUEST: GET request is an HTTP request method used to retrieve or fetch data from a specified resource
// Function to send GET request to Alpaca API
alpacaStock::responseData alpacaStock::sendGetRequest(const std::string& url) {
    responseData responseData;
    CURL* curl = curl_easy_init();//initialize and perform http request from client to server
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//the url to retrieve the data from
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);//callback function that is responsible for writing the API response data into the responseData struct
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(responseData.response));
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.68.0");//to set User-Agent header for the request.
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &(responseData.http_code));//HTTP response code is retrieved 
        curl_easy_cleanup(curl);
    }
    return responseData;
}