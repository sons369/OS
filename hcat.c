#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int line;

void cat(int fd)
{
    int n;
    int i = 0;

    while ((n = read(fd, buf, 1)) > 0)
    {
        if (!strcmp(buf, "\n"))
            i++;
        if (i == line)
            exit();
        if (write(1, buf, n) != n)
        {
            printf(1, "cat: write error\n");
            exit();
        }
    }
    if (n < 0)
    {
        printf(1, "cat: read error\n");
        exit();
    }
}

int main(int argc, char *argv[])
{
    int fd, i;

    if (argc <= 1)
    {
        cat(0);
        exit();
    }

    for (i = 2; i < argc; i++)
    {
        line = atoi(argv[1]);
        if ((fd = open(argv[i], 0)) < 0)
        {
            printf(1, "cat: cannot open %s\n", argv[i]);
            exit();
        }
        cat(fd);
        close(fd);
    }
    exit();
}
