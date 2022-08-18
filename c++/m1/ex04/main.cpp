#include <iostream>
#include <fstream>

int main(int ac, char **av)
{
	if (ac == 4)
	{
		std::ifstream input;
		std::ofstream output;
		std::string buffer;

		input.open(av[1]);
		if (!input.is_open())
		{
			std::cout << "File error" << std::endl;
			exit(-1);
		}
		while (!input.eof())
		{
			char c = input.get();
			if (c != -1)
				buffer.push_back(c);
		}
		std::string s1 = av[2];
		std::string s2 = av[3];
		int pos = buffer.find(s1);
		if (!pos)
		{
			std::cout << "Can't find occurence" << std::endl;
			exit(-1);
		}
		int j = 0;
		for (int i = 0 ; i < (int)s2.length(); i++)
		{
			if (i >= (int)s1.length())
			{
				std::string s3;
				s3.append(s2, j);
				buffer.insert(pos, s3);
				break;
			}
			else
				buffer[pos++] = s2[j++];
		}
		output.open(std::string(av[1]) + std::string(".replace"));
		output << buffer;
		input.close();
		output.close();
	}
	return (0);
}
