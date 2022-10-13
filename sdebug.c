#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5                  // fork 프로세스 개수
#define PRINT_CYCLE 1000000     // 각 프로세스 정보 출력 주기(틱)
#define TOTAL_COUNTER 500000000 // 프로세스가 종료할 떄 카운터 값(틱)

void sdebug_func(void)
{
    int n, pid;

    printf(1, "start sdebug command\n");

    for (n = 0; n < PNUM; n++)
    {
        pid = fork();
        if (pid < 0)
        {
            break;
        }
        if (pid == 0)
        {
            long cnt = 0;
            int get_weight = weightset(n + 1);
            long start = uptime();

            for (cnt = 0; cnt < TOTAL_COUNTER; cnt++)
            {
                // tmp = uptime();

                // printf(1, "\npid %d %d %d\n", getpid(), tmp, cnt);
                if (cnt == PRINT_CYCLE)
                {
                    long end = uptime();
                    printf(1, "PID: %d, WEIGHT: %d, TIMES : %d ms\n", getpid(), get_weight, (end - start) * 10);
                }
            }
            if (cnt == TOTAL_COUNTER)
            {
                printf(1, "PID: %d terminated\n", getpid());
                exit();
            }
        }
    }

    for (int i = 0; i < PNUM; i++)
    {
        if (pid != 0)
            wait();
    }

    printf(1, "end of sdebug command\n");
}

int main(void)
{
    sdebug_func();

    exit();
}