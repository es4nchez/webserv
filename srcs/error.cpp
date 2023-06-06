#include "error.hpp"

error::error(int fd, std::map<int, std::string> error_code)
{
    e_fd = fd;
	std::map<int,std::string>::iterator it;
	std::vector<std::string> test;
	test[0] = "blou";
	test[1] = "blah";
	e_errorCodes.insert(std::pair<int, std::vector<std::string> >(400, test));
	e_errorCodes[404] = {"404 Not Found", "www/errors/404.html"};
	e_errorCodes[405] = {"405 Method Not Allowed", "www/errors/405.html"};
	e_errorCodes[413] = {"413 Content Too Large", "www/errors/413.html"};
	
	for(it = error_code.begin(); it != error_code.end(); it++)
	{
		e_errorCodes[it->first][1] = error_code[it->second];
	}
    e_size = sizeof(errors) / sizeof(errors[0]);
}

error::~error()
{

}

void    error::send_error(int error_code)
{
	std::string base, name;
    for (int i = 0; i < e_size; ++i) 
	{
        if (error_code == errors[i]) 
		{
            base = "HTTP/1.1 " + errorCodes[i] + "\n\n";
            name = errorFiles[i];
            break;
        }
    }
    std::ifstream file(name.c_str());
    std::stringstream buff;
    buff << file.rdbuf();

    std::string response = base + buff.str();
    send(e_fd, response.c_str(), response.size(), 0);
}