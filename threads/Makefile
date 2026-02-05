
CC=clang
CFLAGS=-Wall -g -std=gnu11
BINS=pthreadex pthreadex2 pthreadex3 conditionex asyncio readwritelockex sem barriers


all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ -pthread


clean:
	rm -rf $(BINS) *.o *.dSYM
