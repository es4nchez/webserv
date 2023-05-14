#include "webserv.hpp"

void Webserv::sendResponse(s_request *requestData, int fd)
{

        std::string path = this->rootPath + requestData->addr.substr(1, requestData->addr.size());
        std::ifstream   file(path.c_str());
        std::stringstream   buff;
        std::string response;

        
        if (isRedirect(path))
        {
                std::string location = "http://localhost:8080/42lWatch.html";
                std::string base = "HTTP/1.1 301 Moved Permanently\n";
                std::string body = "Location: " + location + "\r\n";
                send(client_sockfd[fd], (base + body).c_str(), (base + body).size(), 0);
                return;
        }
        // Try to open the requested file, if it doesnt exist ( empty = 0), send 404
        buff << file.rdbuf();
        std::cout << "size : " <<  buff.str().size() << std::endl << std::endl;
        if (!buff.str().size())
                notFound(fd);
        else
        {
                std::string base = "HTTP/1.1 200 OK\n\n";
                response = base + buff.str();

                send(client_sockfd[fd], response.c_str(), response.size(), 0);
        }
}

// Generic index sending
void Webserv::sendIndex(int fd)
{
        std::string path = this->rootPath + this->index;
        std::ifstream   file(path.c_str());
        std::stringstream   buff;
        std::string response;

        buff << file.rdbuf();
        std::string base = "HTTP/1.1 200 OK\n\n";
        response = base + buff.str();

        send(client_sockfd[fd], response.c_str(), response.size(), 0);
}