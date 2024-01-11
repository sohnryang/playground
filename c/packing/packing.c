#include <stdint.h>
#include <stdio.h>

struct header_flag {
  unsigned int flag1 : 1;
  unsigned int flag2 : 1;
  unsigned int pad : 30;
};

union header {
  uint32_t addr;
  struct header_flag flag;
};

int main() {
  union header header;
  header.addr = 0x12340000;

  header.flag.flag1 = 1;
  printf("9x%x\n", header.flag.flag1);
  printf("9x%x\n", header.flag.flag2);
  printf("0x%x\n", header.addr);

  return 0;
}
