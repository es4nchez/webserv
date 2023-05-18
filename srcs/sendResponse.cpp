#include "webserv.hpp"

void Webserv::sendResponse(s_request *requestData, int fd, int success_code)
{
		const std::string successCodes[] = {"200 OK", "201 Created", "202 Accepted"};
		const int success[] = {200, 201, 202};
		const int size = sizeof(success) / sizeof(success[0]);
		std::string base, name;
		std::string response;
		std::stringstream   buff;
		if (success_code == 200)
		{
			std::string path = _rootpath + requestData->addr.substr(1, requestData->addr.size());
        	std::ifstream   file(path.c_str());
			if (isRedirect(path))
			{
				redirectURL(path, fd);
				return;
			}
			buff << file.rdbuf();
			std::cout << "size : " <<  buff.str().size() << std::endl << std::endl;
			if (!buff.str().size())
				code_error(fd, 404);
		}
		else
			buff << "";
        // Try to open the requested file, if it doesnt exist ( empty = 0), send 404
     	for (int i = 0; i < size; ++i) {
			if (success_code == success[i]) {
				base = "HTTP/1.1 " + successCodes[i] + "\n\n";
				break;
			}
		}
		response = base + buff.str();
		std::cout << response << std::endl;
        send(_client_sockfd[fd], response.c_str(), response.size(), 0);
}


// Generic index sending
void Webserv::sendIndex(int fd)
{
        std::string path = _rootpath + _index;
        std::ifstream   file(path.c_str());
        std::stringstream   buff;
        std::string response;
        buff << file.rdbuf();
        std::string base = "HTTP/1.1 200 OK \n\n";
		response = base + buff.str();

        send(_client_sockfd[fd], response.c_str(), response.size(), 0);
}