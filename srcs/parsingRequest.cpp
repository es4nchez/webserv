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


    sendResponse(data, requestData);


}