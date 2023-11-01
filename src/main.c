#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"
#include <fcntl.h>

int create_process();

int main(int argc, char *argv[]) {
    char buf[100];
    // write(1, "File path: ", 11);
    // read(0, buf, 100);
    int pipe_fd[2];
    int err = pipe(pipe_fd); 
    if (err == -1)
    {
        perror("pipe");
        return -1;
    }
    pid_t pid = create_process();
    if (0 == pid)
    {
        close(pipe_fd[0]);
        // const char *filename = &buf[0];
        // write(1, filename, sizeof(filename));
        int fd = open(argv[1], O_RDONLY, 0);
        dup2(fd, 0);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
        execl("../src/build/child", "child", NULL);
        perror("execl");
        exit(-1);
    }
    else
    {
        close(pipe_fd[1]); 
        float sum;

        while (read(pipe_fd[0], &sum, sizeof(sum)) > 0) {
            char c[32];
            sprintf(c, "%g", sum);
            write(1, "Sum: ", 5);
            write(1, c, sizeof(c));
            write(1, "\n", 1);
        }; 

        close(pipe_fd[0]); 
        wait(NULL);
    }
    return 0;
}

int create_process() {
    pid_t pid = fork();
    if (-1 == pid)
    {
        perror("fork");
        exit(-1);
    }
    return pid;
}