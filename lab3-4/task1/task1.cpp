// Создайте программу на основе одного исходного (а затем исполняемого)
// файла с псевдораспараллеливанием вычислений посредством порождения
// процесса-потомка.

#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int pid;
    int n = 0;
    int m = 100;
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
            n += 1;
        }
        std::cout << "Parent: " << n << '\n';
    }
    else
    {
        for (int j = 0; j < 100; j++)
        {
            m -= 1;
        }
        std::cout << "Son: " << m << '\n';
    }

    std::cout << "Program done!" << '\n';
    exit(1);
}