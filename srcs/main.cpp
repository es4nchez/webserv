#include "webserv.hpp"
#include "ParserJSON.hpp"
#include "server_conf.hpp"
#include <array>

// For Dev
Webserv *g_webserv = nullptr;

int main(int ac, char **av, char **envp)
{
	Webserv ws;

	try
	{
		std::string file = read_file("./config/sample.json");
		ParserJSON json(file);

		std::cout << json.toString() << std::endl;

		std::vector<ParserJSON::t_lexem>::const_iterator tmp;

		if (!json.keys((std::array<std::string, 3>){"test", "testa", "testb"}, tmp))
		{
			std::cout << tmp->value << std::endl;
		}

		std::cout << "Parsing done" << std::endl;
	}
	catch (const char *err)
	{
		std::cerr << "parse_server_configuration_err" << std::endl;
		std::cerr << err << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "parse_server_configuration" << std::endl;
		std::cerr << e.what() << std::endl;
	}
	return (0);

	// Init args
	if (ws.args(ac, av, envp))
		return (1);

	// HARDCODE CONFIG
	ws.HARDCODE_INIT();

	if (ws.socketBinding())
		return (1);
	std::cout << std::endl
						<< "Webserv launching... start logs :" << std::endl
						<< std::endl;

	while (true)
	{
		// wait for activity on the file descriptors using select()
		fd_set temp__fds = ws._fds;
		int ret = select(ws._max_fd + 1, &temp__fds, NULL, NULL, NULL);
		if (ret == -1)
		{
			std::cerr << "Error in select()" << std::endl;
			break;
		}

		// iterate over the file descriptors to check for activity
		for (unsigned int i = 0; i < ws._ports.size(); i++)
		{
			if (FD_ISSET(ws._sockfd[i], &temp__fds))
			{
				// accept the incoming connection
				ws._client_sockfd[i] = accept(ws._sockfd[i], (sockaddr *)&ws._client_addr[i], &ws._client_len[i]);
				if (ws._client_sockfd[i] < 0)
				{
					std::cerr << "Error accepting connection" << std::endl;
					continue;
				}

				std::string request = ws.receive(i);

				// handle the request
				ws.handleRequest(request, i);

				// close the connection
				close(ws._client_sockfd[i]);
			}
		}
	}

	for (unsigned int i = 0; i < ws._ports.size(); i++)
		close(ws._sockfd[i]);
	return (0);
}