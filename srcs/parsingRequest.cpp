#include "request.hpp"
#include "cgi.hpp"

void Request::handleGET(s_request *requestData, int fd)
{

    CGI cgi(r_client_sockfd, r_config, r_query_string);
	std::string fullPath = "";
	std::string	root = "";
	std::string addr = "";
    if (cgi.is_cgi_request(requestData->addr))
        cgi.handle_cgi_request(r_client_sockfd, (r_route.root + requestData->addr), r_wenvp);
    else
    {
		if (requestData->addr[requestData->addr.size() - 1] == '/' && r_route.index.size() != 0)
		{
			root = r_route.root.substr(0, r_route.root.size() - 1);
			addr = requestData->addr.substr(0, requestData->addr.size() - 1);
			fullPath = root + addr;
			sendIndex(fd);
			return ;
		}
		else
        	fullPath = r_route.root + requestData->addr;
        DIR* dir = opendir(fullPath.c_str());
        if (dir != NULL && r_route.dir_listing)
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
    std::string temp = request.substr(request.find("\r\n\r\n") + 4);
    if (temp.size() > r_config.max_client_body_size )
	{
		r_error->send_error(413);
		return ;
	}
    CGI cgi(r_client_sockfd, r_config, r_query_string);
    if (cgi.is_cgi_request(requestData->addr))
        cgi.handle_cgi_request(r_client_sockfd, (r_route.root + requestData->addr), r_wenvp);
    else
        parsePostRequest(request, fd);
}

void Request::handleDELETE(s_request *requestData, int fd)
{
    deleteRequest(requestData, fd);
}



bool Request::checkMethod(std::string methd)
{
    for (std::vector<e_http_method>::const_iterator it = r_route.methods.begin();
         it != r_route.methods.end(); ++it)
    {
        if (methodToString(*it) == methd)
            return true;
    }
    return false;
}


void Request::mainParsing(std::string request, s_request *requestData, int fd)
{
    std::cout << "Method: " << requestData->methd << std::endl;
    std::cout << "Requested Address: " << requestData->addr << std::endl;

    if (requestData->addr == "/exit")
        exit (1);

    // Print the Data map
    // for (std::map<std::string, std::string>::iterator it = requestData->data.begin(); it != requestData->data.end(); ++it)
    //     std::cout << it->first << " = " << it->second << std::endl;

    // Handle different request types
    if (!checkMethod(requestData->methd))
        r_error->send_error(405);
    else if (!requestData->methd.compare("GET"))
        handleGET(requestData, fd);
    else if (!requestData->methd.compare("POST"))
        handlePOST(request, requestData, fd);
    else if (!requestData->methd.compare("DELETE"))
        handleDELETE(requestData, fd);
    else
        r_error->send_error(405);
}
