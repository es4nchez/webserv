#include "webserv.hpp"

bool isValidPath(const std::string& path)
{
    if (path.find("..") != std::string::npos)
        return false;
    std::string invalidChars = "*:?|<>\"";
    if (path.find_first_of(invalidChars) != std::string::npos)
        return false;

    return true;
}

void Webserv::deleteRequest(s_request *requestData, int fd)
{
    std::string fullPath = _rootpath + requestData->addr;
    if (!isValidPath(requestData->addr))
        code_error(fd, 404);
    else
    {
        std::ifstream file(fullPath);
        if (!file)
            code_error(fd, 404);
        else
        {
            file.close();
            if (std::remove(fullPath.c_str()) == 0)
            {
                std::string response = "HTTP/1.1 202 Accepted\r\nContent-Type: text/plain\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
                send(_client_sockfd[fd], response.c_str(), response.size(), 0);
            } else
                code_error(fd, 500);
        }
    }
}
