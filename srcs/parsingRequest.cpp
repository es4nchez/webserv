#include "../includes/webserv.hpp"

void    mainParsing(c_webserv *data, std::string request, s_request *requestData)
{

    std::size_t space_pos = request.find(' ');

    if (space_pos != std::string::npos) {
        requestData->methd = request.substr(0, space_pos);
        std::size_t next_space_pos = request.find(' ', space_pos + 1);
        if (next_space_pos != std::string::npos) {
            requestData->addr = request.substr(space_pos + 1, next_space_pos - space_pos - 1);
        }
    }
    
    std::cout << "Method: " << requestData->methd << std::endl;
    std::cout << "Requested Address: " << requestData->addr << std::endl;

    if (!requestData->addr.compare("/favicon.ico"))
    {
        std::cout << " FAAAV !" << std::endl;

        std::ifstream   fav("favicon.ico");
        std::stringstream   buff;
        std::string response;

        buff << fav.rdbuf();
        std::string base = "HTTP/1.1 200 OK\n\n";
        response = base + buff.str();

        send(data->client_sockfd, response.c_str(), response.size(), 0);
        std::cout << "omg, its a favicon" << std::endl;
    }
    else
    {
        const char* response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\nHello World!";
        send(data->client_sockfd, response, strlen(response), 0);
    }



}