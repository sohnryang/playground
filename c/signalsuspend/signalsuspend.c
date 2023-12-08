#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t sigchld_sema;
static volatile pid_t pid;

void sigchld_handle(int s) {
  errno_t old_errno = errno;
  pid = waitpid(-1, NULL, 0);
  sigchld_sema = 1;
  errno = old_errno;
}

int main(int argc, char *argv[]) {
  sigset_t mask, prev;
  int n = 10;

  signal(SIGCHLD, sigchld_handle);
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);

  while (n--) {
    sigprocmask(SIG_BLOCK, &mask, &prev);
    puts("Spawning child...");
    if (fork() == 0) {
      puts("Child spawned");
      exit(0);
    }

    sigchld_sema = 0;
    puts("Wait started");
    while (!sigchld_sema)
      sigsuspend(&prev);
    printf("Wait finished. pid=%d\n", pid);

    sigprocmask(SIG_SETMASK, &prev, NULL);
  }

  return 0;
}
