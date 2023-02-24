#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cpr/cpr.h>

cpr::Response Get(std::map<std::string, std::string>* arguments) {
    std::map<std::string, std::string>::iterator it;

    std::string url= "http://httpbin.org/get";
    url = url.c_str();
    for (it = arguments->begin(); it != arguments->end(); it++) {
        if (it != arguments->begin())
            url += '&' + it->first + '=' + it->second; //+=
        else
            url += '?' + it->first + '=' + it->second; //+=
    }

    return cpr::Get(cpr::Url(url));
}

cpr::Response Post(std::map<std::string, std::string>* arguments) {
    std::map<std::string, std::string>::iterator it;
    std::vector <cpr::Pair> requests;
    for (it = arguments->begin(); it != arguments->end(); it++) {
        requests.push_back(cpr::Pair((std::string)it->first.c_str(), (std::string)it->second.c_str()));
    }

    return cpr::Post(cpr::Url("http://httpbin.org/post"),
              cpr::Payload({requests.begin(), requests.end()}));
}

int main() {
    std::map<std::string, std::string> arguments;
    std::string argument = "unknown1";
    do {
        std::cout << "Enter the name of the argument and its value separated by a space:\n";
        std::string value = "unknown2";
        std::cin >> argument >> value;

        if (argument != "get" && argument != "post")
            arguments.insert(std::pair<std::string, std::string>(argument.c_str(), value.c_str()));
    } while((argument != "get" && argument != "post") || arguments.empty());

    if (argument == "get")
        std::cout << Get(&arguments).text << "\n";
    else
        std::cout << Post(&arguments).text << "\n";
}