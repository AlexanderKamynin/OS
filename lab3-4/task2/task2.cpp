#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int pid;
    pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    std::cout << "pid: " << pid << '\n';
    if(pid != 0)
    {
        for (int i = 0; i < 100; i++)
        {
            std::cout << "step = " << i << ",parent cycle with pid: " << pid << '\n';
        }
    }
    else
    {
        for (int i = 0; i < 100; i++)
        {
            std::cout << "step = " << i << ",son cycle with pid: " << pid << '\n';
        }
    }

    std::cout << "Program done from pid: " << pid << '\n';
    exit(1);
}