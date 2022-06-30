#include "types.h"
#include "stat.h"
#include "user.h"

#define CHILDREN 3
#define LIMIT 5

int main() {
    changePolicy(1);
    
    for (int i = 0; i < CHILDREN; i++) {
        int pid = fork();
        if (pid == 0) {
            for (int i = 0; i < LIMIT; i++)
                printf(1, "/%d/ : /%d/\n", getpid(), i);
            sleep(100);
            exit();
        }
    }

    int TATSum = 0, WTSum  = 0, CBTSum = 0;

    for (int i = 0; i < CHILDREN; i++) {
        int pid = wait();

        int ctime  = getProcStatus(pid, 0);
        int ttime  = getProcStatus(pid, 1);
        int rntime = getProcStatus(pid, 2);
        int rdtime = getProcStatus(pid, 3);
        int stime  = getProcStatus(pid, 4);
        
        int TAT = ttime - ctime;
        int WT  = rdtime;
        int ST  = stime;
        int CBT = rntime;

        TATSum += TAT;
        WTSum += WT;
        CBTSum += CBT;

        printf(1, "> pid: %d\n", pid);
        printf(1, "  creation time = %d - ", ctime);
        printf(1, "termination time = %d - ", ttime);
        printf(1, "turnaround time = %d - ", TAT);
        printf(1, "waiting time = %d - ", WT);
        printf(1, "sleeping time = %d - ", ST);
        printf(1, "CPU burst = %d", CBT);
        printf(1,"\n\n");
    }

    printf(1, "\n\n> average turnaround time: %d\n", TATSum / 10.0);
    printf(1, "> average waiting time: %d\n", WTSum / 10.0);
    printf(1, "> average CPU burst time: %d\n", CBTSum / 10.0);

    exit();
}