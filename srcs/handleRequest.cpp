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

void            Request::handleRequest(std::string buffer, int fd)
{
    s_request         requestData;
    std::string::size_type    maxCommonLetters = std::string::npos;
      std::string::size_type n;

    getAddrMethodData(buffer, &requestData);
    for(unsigned long i = 0; i < r_config.routes.size(); i++)
    {
        n = requestData.addr.find(r_config.routes[i].location);

        std::cout << " CMP"  << requestData.addr << "  "  << r_config.routes[i].location << "   "  << n << std::endl;

        if (n != std::string::npos && n < maxCommonLetters) {
            std::cout << " match " << std::endl;
            r_route = r_config.routes[i];
            maxCommonLetters = n;
        }


        // if (nbCommonLetters(requestData.addr, r_config.routes[i].location) > maxCommonLetters)
        //     maxCommonLetters = nbCommonLetters(requestData.addr, r_config.routes[i].location);

        //     break ;
        // }
        // else if (i == (r_config.routes.size() - 1))
        // {
        //     r_error->send_error(404);
        //     return;
        // }
    }
    if (maxCommonLetters == std::string::npos) {
        r_route = r_config.routes[2];
    }
    mainParsing(buffer, &requestData, fd);
}


// void    		Request::handleRequest(std::string buffer, int fd)
// {
//     s_request 		requestData;
// 	unsigned long	maxCommonLetters = 0;
//   	std::string::size_type n;

// 	getAddrMethodData(buffer, &requestData);
// 	if (!check_hostname(buffer))
// 		return ;
// 	for(unsigned long i = 0; i < r_config.routes.size(); i++)
// 	{
// 		if (nbCommonLetters(requestData.addr, r_config.routes[i].location) > maxCommonLetters)
// 			maxCommonLetters = nbCommonLetters(requestData.addr, r_config.routes[i].location);
// 	}
// 	for(unsigned long i = 0; i < r_config.routes.size(); i++)
// 	{
// 		n = requestData.addr.find(r_config.routes[i].location);
// 		if (requestData.addr.size() == maxCommonLetters && maxCommonLetters == r_config.routes[i].location.size())
// 		{
// 			r_route = r_config.routes[i];
// 			break ;
// 		}
// 		else if (std::string::npos != n)
// 		{
// 			r_route = r_config.routes[i];
// 			break ;
// 		}
// 		else if (i == (r_config.routes.size() - 1))
// 		{
// 			r_error->send_error(404);
// 			return;
// 		}
// 	}
//     mainParsing(buffer, &requestData, fd);
// }

bool Request::check_hostname(std::string address)
{
	std::string temp;
	std::size_t end_pos = address.find('\n');
	temp = address.substr(end_pos + 7, address.size() - end_pos);
	end_pos = temp.find('\n');
	temp = temp.substr(0, end_pos);
	end_pos = temp.find(':');
	temp = temp.substr(0, end_pos);
	// if (r_server_names.compare(temp))
	// {
	// 	code_error(400);
	// 	return false;
	// }
	return true;
}