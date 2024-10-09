CC=clang
CFLAGS=--sysroot=/opt/riscv/sysroot -march=rv64gcv -O3
OBJS=driver.o matmul-naive.o

all: driver.naive driver.vectorized

driver.naive: driver.o matmul-naive.o
	$(CC) $(CFLAGS) -o $@ $^

driver.vectorized: driver.o matmul-vectorized.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o driver.naive driver.vectorized
