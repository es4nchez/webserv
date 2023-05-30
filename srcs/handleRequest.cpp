#include "request.hpp"

unsigned long	Request::nbCommonLetters(std::string requestLocation, std::string routeLocation)
{
	unsigned long i = 0;
	std::cout << "requestLocation : " << requestLocation << "\n" << "routeLocation : " << routeLocation <<  std::endl;
	while (requestLocation[i] == routeLocation[i] && i < requestLocation.size())
		i++;
	std::cout << "nb fois : " << i << std::endl;
	return (i);
}



void    		Request::handleRequest(std::string buffer, int fd)
{
    s_request 		requestData;
	unsigned long	maxCommonLetters = 0;

	getAddrMethodData(buffer, &requestData);
	for(unsigned long i = 0; i < r_config.routes.size(); i++)
	{
		if (nbCommonLetters(requestData.addr, r_config.routes[i].location) > maxCommonLetters)
			maxCommonLetters = nbCommonLetters(requestData.addr, r_config.routes[i].location);
	}
	for(unsigned long i = 0; i < r_config.routes.size(); i++)
	{
		if (nbCommonLetters(requestData.addr, r_config.routes[i].location) == maxCommonLetters && requestData.addr.size() == maxCommonLetters)
		{
			std::cout << "The good route is : " << r_config.routes[i].location << std::endl;
			break ;
		}
		else
		{
			std::cout << "The good route is : " << r_config.routes[0].location << std::endl;
			break;
		}
	}
	return ;
    mainParsing(buffer, &requestData, fd);
}