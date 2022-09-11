#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char userID[16][32];
char pwdID[16][32];

void get_user_list()
{
    int fd;
    int n;
    int flag = 0;
    char buf[512];
    int idx = 0;
    int q_idx = 0;

    fd = open("list.txt", O_RDONLY);

    for (int i = 0; i < 16; i++)
    {
        while ((n = read(fd, buf, 1)) > 0)
        {
            if (buf[0] == '\n')
                break;
            else if (buf[0] == ' ')
                flag = 1;
            else if (flag == 0)
                userID[i][idx++] = buf[0];
            else
            {
                pwdID[i][q_idx++] = buf[0];
            }
        }
        idx = 0;
        q_idx = 0;
        flag = 0;
    }
    close(fd);
}

int check_idpw(const char *user_id, const char *user_pw)
{
    if (strlen(user_id) == 0 || strlen(user_pw) == 0)
        return 0;
    for (int i = 0; i < 10; i++)
    {
        if (!strcmp(user_id, userID[i]))
            if (!strcmp(user_pw, pwdID[i]))
                return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int pid, wpid;
    char id[32];
    char pw[32];

    get_user_list();

    while (1)
    {
        printf(1, "Username: ");
        gets(id, 32);
        id[strlen(id) - 1] = '\0';
        printf(1, "Password: ");
        gets(pw, 32);
        pw[strlen(pw) - 1] = '\0';
        if (check_idpw(id, pw))
            break;
    }

    pid = fork();
    if (pid < 0)
    {
        printf(1, "init: fork failed\n");
        exit();
    }
    if (pid == 0)
    {
        exec("sh", argv);
        printf(1, "init: exec sh failed\n");
        exit();
    }
    while ((wpid = wait()) >= 0 && wpid != pid)
        printf(1, "zombie!\n");
    return 0;
}