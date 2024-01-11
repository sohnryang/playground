#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigint_handle(int arg) { puts("I refuse to be interrupted."); }

int main(int argc, char *argv[]) {
  signal(SIGINT, sigint_handle);
  pause();
  return 0;
}
