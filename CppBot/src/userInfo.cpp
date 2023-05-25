#include"userInfo.h"
userInformation::userInformation(std::string data) {
    // std::cout << "here1" << std::endl;
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