#include "includes.hpp"

uintptr_t serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int main()
{
	Data data;
	std::cout << &data << std::endl;
	std::cout << serialize(&data) << std::endl;
	std::cout << deserialize(serialize(&data)) << std::endl;
	return (0);
}
