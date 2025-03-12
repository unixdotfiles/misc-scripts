CFLAGS+=-Weverything -g

PROGS=	abort detect-broken-poll wordcheck getrusage gmtime-print empty charcheck
all:	$(PROGS)
# not in all since it doesn't work on arm mac (for obvious reasons)
spectre:
clean:
	rm -f $(PROGS)
