#ifndef LIB_NAME_HPP
#define LIB_NAME_HPP

#include <iostream>

#include <sstream>
#include <memory>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <vector>
#include <string>

namespace myWeb {

class Website {
public:
    Website() = delete;
    Website(std::string url);
    std::string get(std::string loc, int maxsize);
    ~Website();

private:
    struct SSLHelper;
    std::unique_ptr<SSLHelper> sslHelper;

    int status, sock;
    struct addrinfo hints;
    struct addrinfo *servinfo;


    long res = 1;

    struct URL {
        std::string host;
        std::string port;
        std::string protocol;
    };
    URL url;
    void sendToSite(std::string request);
    void recvFromSite(char buf[], int maxsize);
    void establishConn();
    void parseUrl(std::string url);

};

}

#endif
