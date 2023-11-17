#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  bool a_flag = false, b_flag = false;
  char *c_str = NULL, *d_str = NULL;
  int ch;

  opterr = 0;
  while ((ch = getopt(argc, argv, "abc:d:")) != -1) {
    switch (ch) {
    case 'a':
      a_flag = true;
      break;
    case 'b':
      b_flag = true;
      break;
    case 'c':
      c_str = optarg;
      break;
    case 'd':
      d_str = optarg;
      break;
    case '?':
      if (optopt == 'c' || optopt == 'd')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
      return 1;
    default:
      abort();
    }
  }

  printf("a_flag = %d, b_flag = %d, c_str = %s, d_str = %s\n", a_flag, b_flag,
         c_str, d_str);

  for (int i = optind; i < argc; i++)
    printf("Non-option argv[%d] = %s\n", i, argv[i]);
  return 0;
}
