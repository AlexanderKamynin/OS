#include <iostream>
#include <unistd.h>

int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();

    std::cout << "SON PARAMS: pid=" << pid << " ppid=" << ppid << '\n';
    sleep(15);

    return 0;
}