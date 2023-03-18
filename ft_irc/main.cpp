#include "ircserv.hpp"
#include "Server.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	try
	{
		Server serv(atoi(av[1]), av[2]);
		int ret = serv.init();
		if (ret)
			close(serv.sock());
		if (ret || ret == -1)
			return (1);
		serv.loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception::" << e.what() << std::endl;
		return (1);
	}
	return (0);
}
