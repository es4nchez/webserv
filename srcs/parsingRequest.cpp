#include "webserv.hpp"
#include "CGI.hpp"

void    Webserv::mainParsing(std::string request, s_request *requestData, int fd)
{

    std::size_t space_pos = request.find(' ');

    // Find the method and the address in the request 
    if (space_pos != std::string::npos) {
        requestData->methd = request.substr(0, space_pos);
        std::size_t next_space_pos = request.find(' ', space_pos + 1);
        if (next_space_pos != std::string::npos) {
            requestData->addr = request.substr(space_pos + 1, next_space_pos - space_pos - 1);
        }
    }
    
    // Print method and requested address
    std::cout << "Method: " << requestData->methd << std::endl;
    std::cout << "Requested Address: " << requestData->addr << std::endl;

    // If request contain only '/', send index, if else, send file
    if (!requestData->methd.compare("GET"))
    {
        CGI cgi;
        if (cgi.is_cgi_request(requestData->addr))
            cgi.handle_cgi_request(client_sockfd[fd], (rootPath + requestData->addr), wenvp);
        else if (requestData->addr.size() == 1)
            sendIndex(fd);
        else
            sendResponse(requestData, fd);
    }
    else if (!requestData->methd.compare("POST"))
    {
        //
    }
    else if (!requestData->methd.compare("DELETE"))
    {
    
    }
    else
    {
        badMethod(fd);
    }
}