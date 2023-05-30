#include <iostream>
#include <wait.h>
#include <unistd.h>

int main()
{
    int pid, ppid, status;

    pid = getpid();
    ppid = getppid();
    std::cout << "FATHER PARAM: pid=" << pid << " ppid=" << ppid << "\n";

    if (fork() == 0){
        execl("son", "son", NULL);
    }

    system("ps xf > log.txt");
    wait(&status);
    std::cout << "Child process is finished with status: " << status << '\n';
    return 0;
}