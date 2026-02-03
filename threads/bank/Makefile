
CC=clang
CFLAGS=-Wall -g
BINS=mybank


all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ -pthread

mybank: interactivebank.c bank.o
	$(CC) $(CFLAGS) -o $@ interactivebank.c bank.o -pthread

clean:
	rm -rf $(BINS) *.o *.dSYM
