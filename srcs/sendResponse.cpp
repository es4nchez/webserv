#include "../includes/webserv.hpp"

void sendResponse(c_webserv *data, s_request *requestData)
{
        std::string path = data->rootPath + requestData->addr.substr(1, requestData->addr.size());
        std::ifstream   file(path);
        std::stringstream   buff;
        std::string response;

        // Try to open the requested file, if it doesnt exist ( empty = 0), send 404
        buff << file.rdbuf();
        std::cout << "size : " <<  buff.str().size() << std::endl << std::endl;
        if (!buff.str().size())
                notFound(data);
        else
        {
                std::string base = "HTTP/1.1 200 OK\n\n";
                response = base + buff.str();

                send(data->client_sockfd, response.c_str(), response.size(), 0);
        }
}

// Generic index sending
void sendIndex(c_webserv *data)
{
        std::string path = data->rootPath + data->index;
        std::ifstream   file(path);
        std::stringstream   buff;
        std::string response;

        buff << file.rdbuf();
        std::string base = "HTTP/1.1 200 OK\n\n";
        response = base + buff.str();

        send(data->client_sockfd, response.c_str(), response.size(), 0);
}