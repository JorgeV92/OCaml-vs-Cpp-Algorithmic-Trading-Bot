#pragma once
#include<unordered_map>
#include<string>
#include<iostream>
class userInformation {
    public:
    userInformation(std::string data);//constructor
    private:
    std::unordered_map<std::string, std::string> info;
};