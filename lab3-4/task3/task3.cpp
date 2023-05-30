#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int pid;
    int n = 0;
    int m = 100;
    int counter = 0;
    pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    while(true)
    {
        std::cout << "pid: " << pid << '\n';
        if(pid != 0)
        {
            for (int i = 0; i < 10; i++)
            {
                n += 1;
            }
            std::cout << "Parent: " << n << '\n';
        }
        else
        {
            for (int j = 0; j < 10; j++)
            {
                m -= 1;
            }
            std::cout << "Son: " << m << '\n';
        }
        counter++;
        if (counter == 50){
            break;
        }
    }
    
    std::cout << "Program done!" << '\n';
    exit(1);
}