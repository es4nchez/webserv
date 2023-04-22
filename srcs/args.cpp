#include "webserv.hpp"



int Webserv::args(int ac, char **av, char **envp)
{
    if (ac > 2)
    {
        std::cerr << std::endl << "Usage: " << av[0] << " [configuration file]" << std::endl;
        return (1);
    }
    else if (ac == 1)
    {
        std::cout << std::endl <<  "Loading default config file : config/default.conf" << std::endl;
        this->configPath = "config/default.conf";
    }
    else
    {
        std::cout << std::endl << "Loading config file : " << av[1] << std::endl;
        this->configPath = av[1];
    }
    
    for (int i = 0; envp[i] != NULL; i++) {
        char *equals = strchr(envp[i], '=');
        if (equals != NULL) {
            std::string key(envp[i], equals - envp[i]);
            std::string value(equals + 1);
            env[key] = value;
        }
    }

    return (0);
}