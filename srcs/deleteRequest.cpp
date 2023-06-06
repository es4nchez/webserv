#include "request.hpp"

bool isValidPath(const std::string& path)
{
    if (path.find("..") != std::string::npos)
        return false;
    std::string invalidChars = "*:?|<>\"";
    if (path.find_first_of(invalidChars) != std::string::npos)
        return false;

    return true;
}

void Request::deleteRequest(s_request *requestData, int fd)
{
    std::string fullPath = r_rootpath + requestData->addr;
    if (!isValidPath(requestData->addr))
		r_error->send_error(404);
    else if (std::remove(fullPath.c_str()) == 0)
    {
       sendResponse(NULL, fd, 202);
    }
    else
        r_error->send_error(404);
}
