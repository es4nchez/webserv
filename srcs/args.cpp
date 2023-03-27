#include "../includes/webserv.hpp"

int args(c_webserv *data, int ac, char **av)
{
    if (ac > 2)
    {
        std::cerr << std::endl << "Usage: " << av[0] << " [configuration file]" << std::endl;
        return (1);
    }
    else if (ac == 1)
    {
        std::cout << std::endl <<  "Loading default config file : config/default.conf" << std::endl;
        data->configPath = "config/default.conf";
    }
    else
    {
        std::cout << std::endl << "Loading config file : " << av[1] << std::endl;
        data->configPath = av[1];
    }
    return (0);
}