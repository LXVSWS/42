#include "ircserv.hpp"
#include "Client.hpp"
#include "Server.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	Server serv(atoi(av[1]), av[2]);
	if (serv.init())
		return (1);
	if (serv.loop())
		close(serv.sock());
	return (0);
}
