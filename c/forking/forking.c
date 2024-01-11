#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigchld_handle(int arg) { puts("Child exited"); }

int main() {
  pid_t pid;
  char **exec_argv;
  sigset_t mask_chld, prev_mask;

  signal(SIGCHLD, sigchld_handle);

  pid = fork();
  if (pid == 0) {
    puts("Hello from child process");
    exec_argv = calloc(2, sizeof(char *));
    exec_argv[0] = "-l";
    execve("/bin/ls", exec_argv, NULL);
  } else {
    sleep(1);
    printf("Hello from parent process (child pid=%d)\n", pid);
  }

  return 0;
}
