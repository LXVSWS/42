#include "minitalk.h"

int main(int ac, char **av)
{
    if (ac)
    {
        write(1, "client", 6);
    }
    (void)av;
}