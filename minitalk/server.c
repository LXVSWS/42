#include "minitalk.h"

int main(int ac, char **av)
{
    if (ac)
    {
        char *pid = itoa(getpid());
        write(1, "PID : ", 6);
        write(1, pid, strlen(pid));
        write(1, "\n", 1);
        free(pid);
    }
    (void)av;
}
