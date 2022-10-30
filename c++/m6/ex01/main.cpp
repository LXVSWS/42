#include "Data.hpp"

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
	std::cout << "Pointeur d'origine: " << &data << std::endl;
	std::cout << "Adresse serialized: " << serialize(&data) << std::endl;
	std::cout << "Retour deserialize: " << deserialize(serialize(&data)) << std::endl;
	return (0);
}
