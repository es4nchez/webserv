#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>
#include "server_conf.hpp"
#include "error.hpp"

struct s_request {

    std::string methd;
    std::string addr;
    std::map<std::string, std::string> data;

};

class	Request 
{
	public :

	Request(int client_sock_fd, char **envp, s_server w_config);
	~Request();

	int                            		r_client_sockfd;

	std::string 						r_index;
    std::string 						r_rootpath;
    size_t      						r_maxBodySize;

	char                    			**r_wenvp;

	bool                    			r_dirListing;
    std::map<std::string, std::string> 	r_redirects;

    s_server                            r_config;

	s_route								r_route;

    error                               *r_error;

	// handleRequest.cpp
    void    		handleRequest(std::string buffer, int fd);
	unsigned long	nbCommonLetters(std::string requestLocation, std::string routeLocation);

	// parsingRequest.cpp
    void    		mainParsing(std::string request, s_request *requestData, int fd);
    void    		handleGET(s_request *requestData, int fd);
    void    		handlePOST(std::string request, s_request *requestData, int fd);
    void    		handleDELETE(s_request *requestData, int fd);
    bool    		checkMethod(std::string methd);

	// parsingRequestUtils.cpp
    void        	getAddrMethodData(std:: string request, s_request *requestData);
    void        	addQueryEnv(std::string str);
    std::string 	url_decode(const std::string& str);
    std::string 	methodToString(e_http_method method);

    // sendResponse.cpp
    void    		sendResponse(s_request *requestData, int fd, int success_code);
    void    		sendIndex(int fd);

    // postRequest.cpp
    void            parsePostRequest(std::string request, int fd);
    std::string     parseBody(std::string request_body);
    std::string     getFilename(std::string request_data);

    // deleteRequest.cpp
    void            deleteRequest(s_request *requestData, int fd);

	// directoryListing.cpp
    void        	directoryListing(s_request *requestData, int fd);
    std::string 	listFilesInDirectory(const std::string& directoryPath);

    // redirects.cpp
    bool        	isRedirect();
    void        	redirectURL(std::string path, int fd);

    // errorResponses.cpp
    void    		code_error(int error_code);
    void    		badMethod(int fd);
};

#endif