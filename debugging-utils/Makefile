PROGS=	abort wordcheck getrusage gmtime-print spectre
all:	$(PROGS)
spectre: spectre.c
	$(CC) -w -o $(.TARGET) $(.ALLSRC)
clean:
	rm -f $(PROGS)
