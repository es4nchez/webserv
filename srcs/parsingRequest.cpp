#include "request.hpp"
#include "cgi.hpp"

void Request::handleGET(s_request *requestData, int fd)
{
    CGI cgi;
    if (cgi.is_cgi_request(requestData->addr))
        cgi.handle_cgi_request(r_client_sockfd, (r_rootpath + requestData->addr), r_wenvp);
    else if (requestData->addr.size() == 1)
        sendIndex(fd);
    else
    {
        std::string fullPath = r_rootpath + requestData->addr;
        DIR* dir = opendir(fullPath.c_str());
        if (dir != NULL && r_dirListing)
        {
            closedir(dir);
            directoryListing(requestData, fd);
        }
        else
            sendResponse(requestData, fd, 200);
    }
}

void Request::handlePOST(std::string request, s_request *requestData, int fd)
{
    CGI cgi;
    if (cgi.is_cgi_request(requestData->addr))
        cgi.handle_cgi_request(r_client_sockfd, (r_rootpath + requestData->addr), r_wenvp);
    else
        parsePostRequest(request, fd);
}

void Request::handleDELETE(s_request *requestData, int fd)
{
    deleteRequest(requestData, fd);
}

void Request::mainParsing(std::string request, s_request *requestData, int fd)
{
    getAddrMethodData(request, requestData);
    // std::cout << "Method: " << requestData->methd << std::endl;
    // std::cout << "Requested Address: " << requestData->addr << std::endl;

    // Print the Data map
    // for (std::map<std::string, std::string>::iterator it = requestData->data.begin(); it != requestData->data.end(); ++it)
    //     std::cout << it->first << " = " << it->second << std::endl;

    // Handle different request types
    if (!requestData->methd.compare("GET"))
        handleGET(requestData, fd);
    else if (!requestData->methd.compare("POST"))
        handlePOST(request, requestData, fd);
    else if (!requestData->methd.compare("DELETE"))
        handleDELETE(requestData, fd);
    else
        code_error(fd, 405);
}
