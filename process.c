#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // Step 2: Declare PID, PID1, PID2
    pid_t pid, pid1, pid2;

    // Step 3: Call fork()
    pid1 = fork();
    
    // Step 4: if fork() == -1 exit
    if (pid1 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // Step 5: if fork() != -1 getpid()
    pid2 = getpid();
    
    // Step 6: Print PID
    printf("Process ID: %d, Parent Process ID: %d\n", pid2, getppid());
    
    // Step 7: Exit
    exit(EXIT_SUCCESS);
}

