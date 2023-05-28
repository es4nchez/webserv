#include "request.hpp"
#include "cgi.hpp"

std::string url_decode(const std::string& str)
{
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

void Request::addQueryEnv(std::string str) {
    int size = 0;
    bool queryStringExists = false;

    str = "QUERY_STRING=" + str;

    if (r_wenvp != NULL) {
        while (r_wenvp[size] != NULL) {
            if (strncmp(r_wenvp[size], "QUERY_STRING=", 13) == 0) {
                queryStringExists = true;
                delete[] r_wenvp[size];
                char *newStr = new char[str.size() + 1];
                std::copy(str.begin(), str.end(), newStr);
                newStr[str.size()] = '\0';
                r_wenvp[size] = newStr;
            }
            size++;
        }
    }
    if (!queryStringExists) {
        char** newEnvTab = new char*[size + 2];
        for (int i = 0; i < size; i++) {
            newEnvTab[i] = r_wenvp[i];
        }
        char *newStr = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), newStr);
        newStr[str.size()] = '\0';
        newEnvTab[size] = newStr;
        newEnvTab[size + 1] = NULL;
        
        r_wenvp = newEnvTab;
    }
}


void    Request::getAddrMethodData(std:: string request, s_request *requestData)
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