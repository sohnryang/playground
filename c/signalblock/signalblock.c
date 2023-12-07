#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  sigset_t mask_int, prev_mask;
  char buf[10];

  sigemptyset(&mask_int);
  sigaddset(&mask_int, SIGINT);
  sigprocmask(SIG_BLOCK, &mask_int, &prev_mask);
  printf("SIGINT is blocked!\n");

  while (true) {
    printf("To unblock SIGINT, type `unblock`: ");
    fgets(buf, 10, stdin);
    if (strncmp(buf, "unblock", 7) == 0)
      break;
  }

  sigprocmask(SIG_SETMASK, &prev_mask, NULL);
  printf("SIGINT is unblocked!\n");
  printf("Type a farewell message: ");
  fgets(buf, 10, stdin);
  printf("Bye!\n");

  return 0;
}
