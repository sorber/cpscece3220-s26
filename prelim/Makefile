
CC=clang
CFLAGS=-Wall -g

BINS=mystery1 mystery2 mystery3 mystery4 


all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $?



clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM
