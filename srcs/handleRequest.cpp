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
  	std::string::size_type n;

	getAddrMethodData(buffer, &requestData);
	for(unsigned long i = 0; i < r_config.routes.size(); i++)
	{
		if (nbCommonLetters(requestData.addr, r_config.routes[i].location) > maxCommonLetters)
			maxCommonLetters = nbCommonLetters(requestData.addr, r_config.routes[i].location);
	}
	for(unsigned long i = 0; i < r_config.routes.size(); i++)
	{
		n = requestData.addr.find(r_config.routes[i].location);
		if (requestData.addr.size() == maxCommonLetters && maxCommonLetters == r_config.routes[i].location.size())
		{
			r_route = r_config.routes[i];
			break ;
		}
		else if (std::string::npos != n)
		{
			r_route = r_config.routes[i];
			break ;
		}
		else if (i == (r_config.routes.size() - 1))
		{
			code_error(404);
			return;
		}
	}
    mainParsing(buffer, &requestData, fd);
}