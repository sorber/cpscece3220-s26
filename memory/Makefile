
CC=gcc
CFLAGS=-Wall -g3

BINS=address pagesize memterm1 memterm2 memterm3 mmap_example brk_example clztest
all: $(BINS)

norva:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

rva:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space


%: %.c
	$(CC) $(CFLAGS) -o $@ $<

%.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(BINS) *.o *.s a.out *.dSYM