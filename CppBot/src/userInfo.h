#pragma once
#include<unordered_map>
#include<string>
#include<iostream>
#include<fstream>
class userInformation {
    public:
    userInformation(std::string data,std::string realKey,std::string realSecret);
    void makeUserDB();
    //void removeLastCharacter();
    private:
    std::unordered_map<std::string, std::string> info;
    std::string apiKey;
    std::string apiSecret;
};