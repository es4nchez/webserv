#include "webserv.hpp"
#include "cgi.hpp"

std::string url_decode(const std::string& str) {
    std::string result;
    char ch;
    size_t i, j;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            sscanf(str.substr(i + 1, 2).c_str(), "%lx", &j);
            ch = static_cast<char>(j);
            result += ch;
            i += 2;
        } else {
            result += str[i];
        }
    }
    return result;
}

void Webserv::addQueryEnv(std::string str) {
    int size = 0;
    bool queryStringExists = false;

    str = "QUERY_STRING=" + str;

    if (_wenvp != NULL) {
        while (_wenvp[size] != NULL) {
            if (strncmp(_wenvp[size], "QUERY_STRING=", 13) == 0) {
                queryStringExists = true;
                delete[] _wenvp[size];
                char *newStr = new char[str.size() + 1];
                std::copy(str.begin(), str.end(), newStr);
                newStr[str.size()] = '\0';
                _wenvp[size] = newStr;
            }
            size++;
        }
    }
    if (!queryStringExists) {
        char** newEnvTab = new char*[size + 2];
        for (int i = 0; i < size; i++) {
            newEnvTab[i] = _wenvp[i];
        }
        char *newStr = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), newStr);
        newStr[str.size()] = '\0';
        newEnvTab[size] = newStr;
        newEnvTab[size + 1] = NULL;
        
        _wenvp = newEnvTab;
    }
}


void    Webserv::getAddrMethodData(std:: string request, s_request *requestData)
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

    if (requestData->methd == "POST")
    {
        std::string query_string = request.substr(request.find("\r\n\r\n") + 4);
   //     std::cout << "query_string : " << query_string << std::endl;

        addQueryEnv(query_string);

    }
    

}

void    Webserv::mainParsing(std::string request, s_request *requestData, int fd)
{
    // std::cout << "FULL REQUEST : " << request << std::endl;

    getAddrMethodData(request, requestData);
    std::cout << "Method: " << requestData->methd << std::endl;
    std::cout << "Requested Address: " << requestData->addr << std::endl;
    
    // Print the Data map
    for (std::map<std::string, std::string>::iterator it = requestData->data.begin(); it != requestData->data.end(); ++it)
        std::cout << it->first << " = " << it->second << std::endl;

    // If request contain only '/', send index, if else, send file
    if (!requestData->methd.compare("GET"))
    {
        CGI cgi;
        if (cgi.is_cgi_request(requestData->addr))
            cgi.handle_cgi_request(_client_sockfd[fd], (_rootpath + requestData->addr), _wenvp);
        else
        {
            std::string fullPath = _rootpath + requestData->addr;
            DIR* dir = opendir(fullPath.c_str());
            if (dir != NULL && _dirListing)
            {
                closedir(dir);
                directoryListing(requestData, fd);
            } 
            else if (requestData->addr.size() == 1)
                sendIndex(fd);
            else
                sendResponse(requestData, fd);
        }
    }
    else if (!requestData->methd.compare("POST"))
    {
        CGI cgi;
        if (cgi.is_cgi_request(requestData->addr))
            cgi.handle_cgi_request(_client_sockfd[fd], (_rootpath + requestData->addr), _wenvp);
        else
            parsePostRequest(request, _client_sockfd[fd]);
    }
    else if (!requestData->methd.compare("DELETE"))
    {
        deleteRequest(requestData, fd);
    }
    else
    {
        badMethod(fd);
    }
}