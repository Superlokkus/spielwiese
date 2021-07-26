#include <lib_name/lib_name.hpp>

#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/conf.h>

namespace myWeb {

struct Website::SSLHelper {
    SSL_CTX *ctx = nullptr;
    BIO *web = nullptr, *out = nullptr;
    SSL *ssl = nullptr;
    int ssl_sock{};

    SSLHelper(std::string hostName) {
        SSL_library_init();

        const SSL_METHOD *method = TLS_method();
        if ((ctx = SSL_CTX_new(method)) == NULL) throw "Could not create CTX";
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
        SSL_CTX_set_verify_depth(ctx, 4);
        SSL_CTX_set_options(ctx, SSL_OP_ALL);
        if (SSL_CTX_set_default_verify_paths(ctx) == 0) throw "Couldn't se default verify paths";
        if ((ssl = SSL_new(ctx)) == NULL) throw "Couldn't create SSL";
        const char *const PREFERED_CIPHERS = "HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4";
        if (SSL_set_cipher_list(ssl, PREFERED_CIPHERS) != 1) throw "Cipher error";
        if (SSL_set_tlsext_host_name(ssl, hostName.c_str()) != 1) throw "Hostname error";
    }
    void upgrade_ssl(int sock) {
        ssl_sock = SSL_get_fd(ssl);
        if (SSL_set_fd(ssl, sock) == 0) throw "Error setting fd";
        int SSL_status = SSL_connect(ssl);
        switch (SSL_get_error(ssl, SSL_status)) {
            case SSL_ERROR_NONE:
//No error, do nothing
                break;
            case SSL_ERROR_ZERO_RETURN:
                throw "Peer has closed connection";
                break;
            case SSL_ERROR_SSL:
                ERR_print_errors_fp(stderr);
                SSL_shutdown(ssl);

                throw "Error in SSL library";
                break;

            default:
                ERR_print_errors_fp(stderr);
                throw "Unknown error";
                break;

        }
        std::cout << "Ssl connection using " << SSL_get_cipher(ssl) << "\n";
    }
    ~SSLHelper(){
        SSL_free(ssl);
        SSL_CTX_free(ctx);
    }
};

Website::Website(std::string url){
    parseUrl(url);
    if (Website::url.protocol == "http") {
        establishConn();
        std::cout << "Err\n";
    } else if (Website::url.protocol == "https") {
        this->sslHelper = std::make_unique<SSLHelper>(this->url.host);

        establishConn();
        sslHelper->upgrade_ssl(this->sock);
    }
}

std::string Website::get(std::string loc, int maxsize) {
    std::string request = "GET " + loc + "\r\n\r\n";
    char *recvBuf = new char[maxsize];
    memset(recvBuf, 0, strlen(recvBuf));
    Website::sendToSite(request);
    Website::recvFromSite(recvBuf, maxsize);
    std::string reply(recvBuf);
    return reply;
}

Website::~Website() {
    close(sock);
    freeaddrinfo(servinfo);
}

void Website::sendToSite(std::string request){
    if(Website::url.protocol == "http"){
        if (send(sock, request.c_str(), strlen(request.c_str()), 0)  == -1) throw "Error sending message";
    } else if(Website::url.protocol == "https"){
        int len = SSL_write(sslHelper->ssl, request.c_str(), strlen(request.c_str()));
        if(len < 0) throw "Error sending ssl packet";
    }
}

void Website::recvFromSite(char buf[], int maxsize){
    if(Website::url.protocol == "http"){
        if (recv(sock, buf, maxsize, 0) == -1) throw "Error receving message";
    } else if(Website::url.protocol == "https"){
        int amountRead = 0;
        while(amountRead < maxsize){
            int readPart = SSL_read(sslHelper->ssl, buf, maxsize - amountRead);
            if(readPart < 0) throw "Error reccieving message";
            amountRead += readPart;

        }
    }
}

void Website::establishConn(){
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if((status = getaddrinfo(Website::url.host.c_str(), Website::url.port.c_str(), &hints, &servinfo)) != 0) throw "Something wrong with getaddrinfo";
    if((sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) throw "Something wrong with creating socket";
    if((connect(sock, servinfo->ai_addr, servinfo->ai_addrlen)) != 0) throw "Error in connecting to website";
}
//Filles struct Website::url  with host as first argument and path as second
void Website::parseUrl(std::string url){
    // Check wether url is http or https
    if(url.rfind("http://", 0) == 0){
        Website::url.port = "80";
        Website::url.host = url.substr(7);
        Website::url.protocol = "http";
    } else if (url.rfind("https://", 0) == 0){
        Website::url.port = "443";
        Website::url.host = url.substr(8);
        Website::url.protocol = "https";
    } else {
        throw "Invalid url, must start with http:// or https://";
    }
}

}


