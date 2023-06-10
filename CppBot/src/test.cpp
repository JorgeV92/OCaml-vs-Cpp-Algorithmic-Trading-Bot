#include <json/json.h>
#include <iostream>

int main() {
    Json::Value root;
    root["name"] = "John";
    root["age"] = 30;
    root["city"] = "New York";

    Json::StreamWriterBuilder writer;
    std::string output = Json::writeString(writer, root);

    std::cout << output << std::endl;

    return 0;
}
