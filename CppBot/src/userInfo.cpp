#include"userInfo.h"

userInformation::userInformation(std::string data,std::string realKey,std::string realSecret) {
    // std::cout << "here1" << std::endl;
    apiKey = realKey;
    apiSecret = realSecret;
    data.erase(45, 45);
    std::cout << "parsed data is\n";
    std::cout << data << std::endl;
    std::cout << "111111\n";
    // std::cout << "here1" << std::endl;
    std::string keyStr = "";
    std::string valStr = "";
    bool key = true;
    for(int i  = 0; i < data.length(); i++ ) {
        if(data[i] == '{' || data[i] == '}') {
            continue;
        } else if(data[i] == ',') {
            //std::cout << "first is |" << keyStr << "| second is |" << valStr << "|" << std::endl;
            info.insert(std::pair<std::string, std::string>(keyStr, valStr));
            key = !key;//for value
            keyStr = "";
            valStr = "";
            continue;
        } else if(data[i] == ':') {
            key = !key;//for value
            continue;
        }

        if(key) {
            keyStr += data[i];
        } else {//when it's for value
            valStr += data[i];
        }
    }
    //for the last element
    info.insert(std::pair<std::string, std::string>(keyStr, valStr));


    //testing for map
    for(auto it = info.begin(); it != info.end(); ++it) {
        std::cout << "first is " << it->first << " and second is " << it->second << std::endl;
    }

}
void removeLastCharacter() {
    std::fstream file("userDB.csv", std::ios::in | std::ios::out); 
     if (file.is_open()) {
        file.seekg(0, std::ios::end);//Move the read position to the end of the file
        std::streampos fileSize = file.tellg(); // Get the file size

        if (fileSize > 0) {
            file.seekg(-1, std::ios::end);//Move the read position to the last character
            char lastCharacter;
            file.get(lastCharacter);
            file.seekp(-1, std::ios::end);//Move the write position to the last character
            file.put('\0');
            file.close(); // Close the file

            //std::cout << "Last character removed from the file." << std::endl;
        } else {
            std::cout << "File is empty." << std::endl;
        }
    }
}
void userInformation::makeUserDB() {
    std::string userDBFile = "userDB.csv";
    // Check if the file exists
    std::ifstream inputFile(userDBFile);
    bool fileExists = inputFile.good();
    inputFile.close();

    std::ofstream outputFile(userDBFile, std::ios::app);//iosapp for writing
    if (fileExists) {
        if (outputFile.is_open()) {
            std::string formattedAPIKey = "\"" + apiKey + "\"";
            std::string formattedAPISecret = "\"" + apiSecret + "\"";
            outputFile << formattedAPIKey << "," << formattedAPISecret << ",";
            for(auto it = info.begin(); it != info.end(); ++it) {
                outputFile << it->second << ',';
            }
            removeLastCharacter();
        } 
    } else {
        std::cout << "File does not exist." << std::endl;
        if (outputFile.is_open()) {
            outputFile << "\"apiKey\",\"apiSecret(HASHED)\"";
            for(auto it = info.begin(); it != info.end(); ++it) {
                outputFile << it->first << ',';
            }
            removeLastCharacter();
            outputFile << "\n";
            std::string formattedAPIKey = "\"" + apiKey + "\"";
            std::string formattedAPISecret = "\"" + apiSecret + "\"";
            outputFile << formattedAPIKey << "," << formattedAPISecret << ",";
            for(auto it = info.begin(); it != info.end(); ++it) {
                outputFile << it->second << ',';
            }
            removeLastCharacter();
            outputFile << "\n";
            outputFile.close();

        }
        

    }
    
 
    
    return;

    
}