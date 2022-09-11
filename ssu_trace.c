#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int pid;
    if (argc < 3)
        exit();

    pid = fork();
    if (pid < 0)
    {
        printf(1, "init: fork failed\n");
        exit();
    }
    if (pid == 0)
    {
        trace(atoi(argv[1]));
        exec(argv[2], &argv[2]);
        printf(1, "error\n");
        exit();
    }
    pid = wait();
    exit();
}