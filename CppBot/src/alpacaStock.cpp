#include "alpacaStock.h"
#include "userInfo.h"

//generates CSV with whole data
void alpacaStock::generateCSV(const std::string& filename) {
    std::ofstream file(filename);//output stream for writing to files
    if(file.is_open()) {
        file << "realTimeTimeStamp," << "openingPrices," << "highestPrices," << "lowestPrices," 
        << "closedPrices," << "volumeOfTrading," << "numberOfTrades," << "vwAveragePrices" << std::endl;
        for(size_t i = 0; i < realTimeTimeStamp.size(); i++) {
            file << realTimeTimeStamp[i] << ",";
            file << openingPrices[i] << ",";
            file << highestPrices[i] << ",";
            file << lowestPrices[i] << ",";
            file << closedPrices[i] << ",";
            file << volumeOfTrading[i] << ",";
            file << numberOfTrades[i] << ",";
            file << vwAveragePrices[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to open the file to put the data." << std::endl;
    }
    return;
}

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

void alpacaStock::storeAccountInfo() {
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
      // std::cout << "Response data: " << responseData << std::endl;
      // std::cout << "\n";
      // std::cout << "\n";
      accountData = responseData;
      

    }


    // Cleanup the things
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    std::cout << "successfully working" << std::endl;
  }
}

std::string alpacaStock::getAccountData() {
  return accountData;
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
std::string alpacaStock::sendGetRequest(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

     // Set up API headers
    struct curl_slist* headers = nullptr;
    if (curl) {
        // Set the URL 
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Set request type
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
      
        
        headers = curl_slist_append(headers, ("APCA-API-KEY-ID: " + apiKey).c_str());
        headers = curl_slist_append(headers, ("APCA-API-SECRET-KEY: " + apiSecret).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set up response storage
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the HTTP request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Error: Failed to perform HTTP request: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        
    } else {
        std::cerr << "Error: Failed initializing cURL" << std::endl;
    }
    std::cout << "\n";
    std::cout << "response is " << response << std::endl;
    // Clean up
    curl_slist_free_all(headers);
  
    return response;
}



void alpacaStock::extractData(std::string stockSymbol, std::string startDate,std::string endDate,std::string timeframe, int limit) {
  // Construct the url using the user input
    std::stringstream url;
    url << "https://data.alpaca.markets/v2/stocks/" << stockSymbol << "/bars"
        << "?start=" << startDate
        << "&end=" << endDate
        << "&timeframe=" << timeframe
        << "&limit=" << limit;

  // Retrieve the complete URL string
  std::string urlString = url.str();
  //std::string url = "https://data.alpaca.markets/v2/stocks/AAPL/bars?start=2022-12-08T09:30:00-04:00&end=2023-06-08T16:00:00-04:00&timeframe=1Day&limit=200";


  //send HTTP getRequest to retrieve data (user specifically required the information)
  std::string responseData = alpacaStock::sendGetRequest(urlString);
  std::cout << "Response is : " << responseData << std::endl;
  infoData =  responseData;
  return;
  
}
void alpacaStock::parseJSONData() {
// Parse the JSON response
  
Json::Value root; // to store the parsed json data
Json::CharReaderBuilder reader; //object that helps in parsing the JSON.
std::istringstream jsonStream(infoData);//to convert jsonData string into an input stream
std::string parseErrors;//to store any error during the parsing

if (Json::parseFromStream(reader, jsonStream, &root, &parseErrors)) {//function to parse the JSON data from the jsonStream into the root object
    if (root.isMember("bars") && root["bars"].isArray()) {
        const Json::Value& bars = root["bars"];
        for (const Json::Value& bar : bars) {
          //t for the time information
            if (bar.isMember("t") && bar["t"].isString()) {
                std::string tValue = bar["t"].asString();
                realTimeTimeStamp.push_back(tValue);
                std::cout << "t: " << tValue << std::endl;
            }
          //o for the opening price information
            if (bar.isMember("o") && bar["o"].isNumeric()) {
                double oValue = bar["o"].asDouble();
                openingPrices.push_back(oValue);
                std::cout << "o: " << oValue << std::endl;
            }
          //h for the highest price information
            if (bar.isMember("h") && bar["h"].isNumeric()) {
                double hValue = bar["h"].asDouble();
                highestPrices.push_back(hValue);
                std::cout << "h: " << hValue << std::endl;
            }
          //l for the lowest price information
            if (bar.isMember("l") && bar["l"].isNumeric()) {
                double lValue = bar["l"].asDouble();
                lowestPrices.push_back(lValue);
                std::cout << "l: " << lValue << std::endl;
            }
          //c for the closed price information
            if (bar.isMember("c") && bar["c"].isNumeric()) {
                double cValue = bar["c"].asDouble();
                closedPrices.push_back(cValue);
                std::cout << "c: " << cValue << std::endl;
            }
          //v for the volumeOfTrading
            if (bar.isMember("v") && bar["v"].isNumeric()) {
                double vValue = bar["v"].asDouble();
                volumeOfTrading.push_back(vValue);
                std::cout << "v: " << vValue << std::endl;
            }
          //n for the number of Trading 
            if (bar.isMember("n") && bar["n"].isNumeric()) {
                double numberOfTrading = bar["n"].asDouble();
                numberOfTrades.push_back(numberOfTrading);
                std::cout << "n: " << numberOfTrading << std::endl;
            }
          //vw for the vwAveragePrices
            if (bar.isMember("vw") && bar["vw"].isNumeric()) {
                double vwavgPrice = bar["vw"].asDouble();
                vwAveragePrices.push_back(vwavgPrice);
                std::cout << "vw: " << vwavgPrice << std::endl;
            }
        } 
    }
} else {
    std::cout << "Failed to parse JSON: " << parseErrors << std::endl;
}
// for (size_t i = 0; i < realTimeTimeStamp.size(); i++) {
//   std::cout << "realTimeStamp is " << realTimeTimeStamp[i] << std::endl;
// }

// for (size_t i = 0; i < closedPrices.size(); i++) {
//   std::cout << "closedPrices is " << closedPrices[i] << std::endl;
// }

  std::string fileName;
  std::cout << "put the filename you want to store the stockInformation!" << std::endl;
  std::cin >> fileName;
  generateCSV(fileName); 
  return;

}
std::vector<double> alpacaStock::extractClosedPrices() {
  return closedPrices;
}
